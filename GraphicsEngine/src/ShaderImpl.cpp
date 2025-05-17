#include "ShaderImpl.h"

#include "Log.h"
#include "SafeGL.h"
#include "Uniform.h"

namespace graphics_engine
{

	namespace
	{

		// Forward declarations of helper functions

		auto CompileShader (
			GLenum shaderType, 
			const char* source
		) -> GLuint;

		auto CompileShadersAndLinkProgram (
			Types::StringView vert, 
			Types::StringView frag, 
			std::optional<Types::StringView> oGeom
		) -> Types::Id;

		auto GetKeys (const Uniforms& uniforms) -> Types::StringViews;
		
		auto InitShader (
			Types::StringView vert, 
			Types::StringView frag, 
			Types::OptStringView oGeom
		) -> std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Uniforms, Types::StringView>;
		
		auto LinkProgram (const std::vector<GLuint>& shaders) -> GLuint;

		auto SetUniformData (
			Types::ShaderId id,
			Uniform& uniform,
			const Types::UniformData& data
		) -> bool;

		// Definitions of helper functions

		auto CompileShader (
			GLenum shaderType, 
			const char* source
		) -> GLuint
		{
			if (source == nullptr)
				return 0;

			GLuint shader = GL::CreateShader (shaderType);
			GL::ShaderSource (shader, 1, &source, nullptr);
			GL::CompileShader (shader);

			auto spLog = GetLog ();

			GLint success;
			GL::GetShaderiv (shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				if (spLog)
					spLog->Error ("Error when compiling shader.");

				GLint infoLogLength;
				GL::GetShaderiv (shader, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog (infoLogLength, '\0');
				GL::GetShaderInfoLog (shader, infoLogLength, nullptr, infoLog.data ());
				if (spLog)
					spLog->Info (infoLog);

				return 0;
			}

			return shader;
		}

		auto CompileShadersAndLinkProgram (
			Types::StringView vert, 
			Types::StringView frag, 
			std::optional<Types::StringView> oGeom
		) -> Types::Id
		{
			auto vertShaderId = CompileShader (GL_VERTEX_SHADER, vert.empty () ? nullptr : std::string (vert).c_str ());
			auto geomShaderId = CompileShader (GL_GEOMETRY_SHADER, oGeom ? std::string (*oGeom).c_str () : nullptr);
			auto fragShaderId = CompileShader (GL_FRAGMENT_SHADER, frag.empty () ? nullptr : std::string (frag).c_str ());
			auto id = LinkProgram ({ vertShaderId, geomShaderId, fragShaderId });
			if (id == 0)
				GetLog ()->Error ("Failed to create shader program.");

			GL::UseProgram (id);

			return id;
		}

		auto GetKeys (const Uniforms& uniforms) -> Types::StringViews
		{
			Types::StringViews keys;
			std::transform (uniforms.begin (), uniforms.end (), std::back_inserter (keys), [] (const std::pair<Types::StringView, Uniform>& uniform)
				{
					return uniform.first;
				});

			return keys;
		}

		/// output tuple is 0: fragment Source, 1: optional geometry source, 2: shader id, 3: uniform names, and 4: vertex source
		auto InitShader (
			Types::StringView vert,
			Types::StringView frag,
			Types::OptStringView oGeom
		) -> std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Uniforms, Types::StringView>
		{
			auto id = CompileShadersAndLinkProgram (vert, frag, oGeom);
			if (id == 0)
			{
				GetLog ()->Error ("CompileShadersAndLinkProgram returned 0.");
				return {};
			}

			// Grab the list of uniforms from the shader.
			GLint count;
			GL::GetProgramiv (id, GL_ACTIVE_UNIFORMS, &count);

			GLint maxLength;
			GL::GetProgramiv (id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

			Uniforms uniforms;
			for (int i = 0; i < count; ++i)
			{
				GLint size;
				GLenum type;
				std::string name (maxLength, '\0');
				GLsizei length; // name length
				GL::GetActiveUniform (id, i, maxLength, &length, &size, &type, name.data ());
				name.resize (length);

				GLint location = GL::GetUniformLocation (id, name.data ());

				Uniform uniform (name, location);
				switch (type)
				{
				case GL_FLOAT:
				{
					float data;
					GL::GetUniformfv (id, location, &data);
					SetUniformData (id, uniform, data);
					break;
				}
				case GL_FLOAT_VEC4:
				{
					std::array<float, 4> v;
					GL::GetUniformfv (id, location, v.data ());
					glm::vec4 data (v[0], v[1], v[2], v[3]);
					SetUniformData (id, uniform, data);
					break;
				}
				case GL_FLOAT_MAT4:
				{
					glm::mat4 m;
					GL::GetUniformfv (id, location, glm::value_ptr (m));
					SetUniformData (id, uniform, m);
					break;
				}
				case GL_SAMPLER_2D:
				{
					int data;
					GL::GetUniformiv (id, location, &data);
					SetUniformData (id, uniform, data);
					break;
				}
				default:
				{
					GetLog ()->Warn (std::format ("Shader uniform type not handled: {}", type));
					break;
				}
				}

				uniforms.try_emplace (name, uniform);
			}

			return std::make_tuple (frag, oGeom, id, uniforms, vert);
		}

		auto LinkProgram (const std::vector<GLuint>& shaders) -> GLuint
		{
			GLuint shaderProgram = GL::CreateProgram ();
			for (auto shader : shaders)
			{
				if (shader != 0)
					GL::AttachShader (shaderProgram, shader);
			}

			GL::LinkProgram (shaderProgram);

			GLint success;
			GL::GetProgramiv (shaderProgram, GL_LINK_STATUS, &success);
			if (!success)
			{
				GLint infoLogLength;
				GL::GetProgramiv (shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

				std::string infoLog (infoLogLength, '\0');
				GL::GetProgramInfoLog (shaderProgram, infoLogLength, nullptr, infoLog.data ());

				return 0;
			}

			for (auto shader : shaders)
			{
				GL::DeleteShader (shader);
			}

			return shaderProgram;
		}

		auto SetUniformData (
			Types::ShaderId id, 
			Uniform& uniform, 
			const Types::UniformData& data
		) -> bool
		{
			if (!GL::IsProgram (id))
				return false;

			uniform.data = data;

			const auto location = uniform.location;
			GL::UseProgram (id);
			if (std::holds_alternative<float> (data))
				GL::Uniform1f (location, std::get<float> (data));
			else if (std::holds_alternative<glm::mat4x4> (data))
				GL::UniformMatrix4fv (location, 1, GL_FALSE, glm::value_ptr (std::get<glm::mat4> (data)));
			else if (std::holds_alternative<glm::vec4> (data))
			{
				auto v = std::get<glm::vec4> (data);
				GL::Uniform4f (location, v[0], v[1], v[2], v[3]);
			}
			else if (std::holds_alternative<int> (data))
				GL::Uniform1i (location, std::get<int> (data));
			else
			{
				GetLog ()->Error ("Data type not handled by Uniform::SetData.");
				return false;
			}

			return true;
		}

	}

	ShaderImpl::ShaderImpl (Types::StringView vert, Types::StringView frag, Types::OptStringView oGeom)
		: ShaderImpl(InitShader(vert, frag, oGeom))
	{
	}

	ShaderImpl::ShaderImpl (const std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Uniforms, Types::StringView>& data)
		:	Shader(std::make_tuple(
				std::get<0>(data),
				std::get<1>(data),
				std::get<2>(data),
				GetKeys(std::get<3>(data)),
				std::get<4>(data)
			)),
			m_Uniforms(Uniforms(std::get<3>(data)))
	{
	}

	auto ShaderImpl::GetUniformData (Types::StringView name) const -> std::optional<Types::UniformData>
	{
		auto itUniform = m_Uniforms.find (name);
		if (itUniform == m_Uniforms.end ())
			return std::nullopt;

		return itUniform->second.data;
	}

	auto ShaderImpl::SetUniformData (Types::StringView name, const Types::UniformData& data) -> bool
	{
		auto itUniform = m_Uniforms.find (name);
		if (itUniform == m_Uniforms.end ())
			return false;

		return graphics_engine::SetUniformData(ID, itUniform->second, data);
	}

	auto ShaderImpl::Use () const -> void
	{
	}

}
