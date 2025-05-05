#include "ShaderManager.h"

#include "IEngine.h"
#include "SafeGL.h"
#include "Shader.h"

namespace GraphicsEngine
{

	ShaderManager::ShaderManager(IEngine* pEngine)
		: m_pEngine(pEngine)
	{
	}

	auto ShaderManager::AddShaderFromFiles(const Path& vert, const Path& frag, const std::optional<Path>& oGeom) -> Id
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

	auto ShaderManager::AddShaderFromSource(StringView vert, StringView frag, std::optional<StringView> oGeom) -> Id
	{
		Shader shader(vert, frag, oGeom);
		if (shader.id != 0)
			m_Shaders.try_emplace(shader.id, shader);

		return shader.id;
	}

	auto ShaderManager::GetCurrentShader() const -> Id
	{
		GLint id;
		GL::GetIntegerv(GL_CURRENT_PROGRAM, &id);

		return id;
	}

	auto ShaderManager::SetUniformData(Id id, StringView name, const UniformData& data) -> void
	{
		m_Shaders.at(id).SetUniformData(name, data);
	}

	auto ShaderManager::UseShader(Id id) const -> void
	{
		GL::UseProgram(id);
	}

}
