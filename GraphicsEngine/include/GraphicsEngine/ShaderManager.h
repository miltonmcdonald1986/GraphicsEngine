#pragma once

#include <optional>
#include <unordered_map>

#include "IShader.h"
#include "Types.h"

namespace GraphicsEngine
{

	class Engine;
	class IEngine;
	class Shader;

	class ShaderManager
	{
	public:
		
		GRAPHICSENGINE_API auto AddShaderFromFiles(const Path& vert, const Path& frag, const std::optional<Path>& oGeom = std::nullopt) -> Id;
		auto AddShaderFromSource(StringView vert, StringView frag, std::optional<StringView> oGeom = std::nullopt) -> Id;
		GRAPHICSENGINE_API auto GetCurrentShader() const->Id;
		GRAPHICSENGINE_API auto SetUniformData(Id id, StringView name, const UniformData& data) -> void;
		auto UseShader(Id id) const -> void;

	private:
		
		friend class Engine;

		explicit ShaderManager(IEngine* pEngine);

		IEngine* m_pEngine = nullptr;
		std::unordered_map<Id, Shader> m_Shaders;

	};

}
