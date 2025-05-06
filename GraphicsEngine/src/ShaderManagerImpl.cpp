#include "ShaderManagerImpl.h"

#include "Fwd.h"
#include "IEngine.h"
#include "Log.h"
#include "SafeGL.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	namespace Helpers
	{

		// Declarations of helper functions.

		auto CompileShader(GLenum shaderType, const char* source) -> GLuint;
		auto CompileShadersAndLinkProgram(StringView vert, StringView frag, std::optional<StringView> oGeom) -> Id;
		auto ErrorMessageShaderWithIdDoesNotExist(ShaderId id) -> String;
		auto LinkProgram(const std::vector<GLuint>& shaders) -> GLuint;

		// Definitions of helper functions.

		auto CompileShadersAndLinkProgram(StringView vert, StringView frag, std::optional<StringView> oGeom) -> Id
		{
			auto vertShaderId = Helpers::CompileShader(GL_VERTEX_SHADER, vert.empty() ? nullptr : std::string(vert).c_str());
			auto geomShaderId = Helpers::CompileShader(GL_GEOMETRY_SHADER, oGeom ? std::string(*oGeom).c_str() : nullptr);
			auto fragShaderId = Helpers::CompileShader(GL_FRAGMENT_SHADER, frag.empty() ? nullptr : std::string(frag).c_str());
			auto id = Helpers::LinkProgram({ vertShaderId, geomShaderId, fragShaderId });
			if (id == 0)
				GetLog()->Error("Failed to create shader program.");

			return id;
		}

		auto CompileShader(GLenum shaderType, const char* source) -> GLuint
		{
			if (source == nullptr)
				return 0;

			GLuint shader = GL::CreateShader(shaderType);
			GL::ShaderSource(shader, 1, &source, nullptr);
			GL::CompileShader(shader);

			auto spLog = GetLog();

			GLint success;
			GL::GetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				if (spLog)
					spLog->Error("Error when compiling shader.");

				GLint infoLogLength;
				GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog(infoLogLength, '\0');
				GL::GetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());
				if (spLog)
					spLog->Info(infoLog);

				return 0;
			}

			return shader;
		}

		auto ErrorMessageShaderWithIdDoesNotExist(ShaderId id) -> String
		{
			return std::format("Shader with id {} does not exist.", id);
		}

		auto LinkProgram(const std::vector<GLuint>& shaders) -> GLuint
		{
			GLuint shaderProgram = GL::CreateProgram();
			for (auto shader : shaders)
			{
				if (shader != 0)
					GL::AttachShader(shaderProgram, shader);
			}

			GL::LinkProgram(shaderProgram);

			GLint success;
			GL::GetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success)
			{
				GLint infoLogLength;
				GL::GetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog(infoLogLength, '\0');
				GL::GetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog.data());

				return 0;
			}

			for (auto shader : shaders)
			{
				GL::DeleteShader(shader);
			}

			return shaderProgram;
		}

	}

	ShaderManagerImpl::ShaderManagerImpl(IEngine* pEngine)
		: m_pEngine(pEngine)
	{
	}

	auto ShaderManagerImpl::AddShader(const Path& vert, const Path& frag, const OptPath& oGeom) -> OptShaderId
	{
		auto GetSourceFromFile = [this](const Path& path) -> String
			{
				if (path.empty())
					return "";

				if (!std::filesystem::exists(path))
				{
					m_pEngine->GetLog()->Error(std::format("Could not open '{}' because it does not exist.", path.string()));
					return "";
				}

				std::ifstream ifs(path);
				std::stringstream buffer;
				buffer << ifs.rdbuf();

				std::string str(buffer.str());
				return str;
			};

		auto vertSource = GetSourceFromFile(vert);
		auto fragSource = GetSourceFromFile(frag);
		std::optional<String> oGeomSource = oGeom ? std::optional<String>(GetSourceFromFile(*oGeom)) : std::nullopt;
		return AddShaderFromSource(vertSource, fragSource, oGeomSource);
	}

	auto ShaderManagerImpl::GetCurrentShader() const -> OptShaderId
	{
		GLint id;
		GL::GetIntegerv(GL_CURRENT_PROGRAM, &id);

		return id == 0 ? std::nullopt : OptShaderId(id);
	}

	auto ShaderManagerImpl::SetUniformData(ShaderId id, StringView name, const UniformData& data) -> bool
	{
		if (!m_Shaders.contains(id))
		{
			GetLog()->Error(Helpers::ErrorMessageShaderWithIdDoesNotExist(id));
			return false;
		}

		auto& uniforms = m_Shaders.at(id);
		auto itUniform = std::ranges::find_if(uniforms, [&name](const Uniform& uniform) { return uniform.name == name; });
		if (itUniform == uniforms.end())
		{
			GetLog()->Error(std::format("Shader {}: Uniform with name {} does not exist.", id, name));
			return false;
		}

		auto& uniform = *itUniform;
		uniform.data = data;

		const auto location = uniform.location;
		GL::UseProgram(id);
		if (std::holds_alternative<float>(data))
			GL::Uniform1f(location, std::get<float>(data));
		else if (std::holds_alternative<glm::mat4x4>(data))
			GL::UniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(std::get<glm::mat4>(data)));
		else if (std::holds_alternative<glm::vec4>(data))
		{
			auto v = std::get<glm::vec4>(data);
			GL::Uniform4f(location, v[0], v[1], v[2], v[3]);
		}
		else if (std::holds_alternative<int>(data))
			GL::Uniform1i(location, std::get<int>(data));
		else
		{
			GetLog()->Error("Data type not handled by Uniform::SetData.");
			return false;
		}

		return true;
	}

	auto ShaderManagerImpl::UseShader(ShaderId id) const -> bool
	{
		if (!m_Shaders.contains(id))
		{
			GetLog()->Error(Helpers::ErrorMessageShaderWithIdDoesNotExist(id));
			return false;
		}

		GL::UseProgram(id);
		return true;
	}

	auto ShaderManagerImpl::AddShaderFromSource(StringView vert, StringView frag, OptStringView oGeom) -> OptShaderId
	{
		auto id = Helpers::CompileShadersAndLinkProgram(vert, frag, oGeom);

		// Grab the list of uniforms from the shader.
		GLint count;
		GL::GetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);

		GLint maxLength;
		GL::GetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

		if (m_Shaders.contains(id))
			m_Shaders.at(id).clear();
		else
			m_Shaders.try_emplace(id);

		for (int i = 0; i < count; ++i)
		{
			GLint size;
			GLenum type;
			std::string name(maxLength, '\0');
			GLsizei length; // name length
			GL::GetActiveUniform(id, i, maxLength, &length, &size, &type, name.data());
			name.resize(strlen(name.c_str()));

			GLint location = GL::GetUniformLocation(id, name.data());

			Uniform uniform(name, location);
			m_Shaders.at(id).push_back(uniform);

			switch (type)
			{
			case GL_FLOAT:
			{
				float data;
				GL::GetUniformfv(id, location, &data);
				SetUniformData(id, name, data);
				break;
			}
			case GL_FLOAT_VEC4:
			{
				std::array<float, 4> v;
				GL::GetUniformfv(id, location, v.data());
				glm::vec4 data(v[0], v[1], v[2], v[3]);
				SetUniformData(id, name, data);
				break;
			}
			case GL_FLOAT_MAT4:
			{
				glm::mat4 m;
				GL::GetUniformfv(id, location, glm::value_ptr(m));
				SetUniformData(id, name, m);
				break;
			}
			case GL_SAMPLER_2D:
			{
				int data;
				GL::GetUniformiv(id, location, &data);
				SetUniformData(id, name, data);
				break;
			}
			default:
			{
				GetLog()->Warn(std::format("Shader uniform type not handled: {}", type));
				break;
			}
			}
		}

		return id == 0 ? std::nullopt : OptShaderId(id);
	}

	auto CreateShaderManagerImpl(IEngine* pEngine) -> ShaderManagerImplPtr
	{
		return std::make_unique<ShaderManagerImpl>(pEngine);
	}

}
