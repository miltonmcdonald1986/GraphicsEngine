#pragma once

#include <optional>
#include <unordered_map>

#include "Types.h"
#include "DllImpExp.h"

namespace GraphicsEngine
{

	class Engine;
	class IEngine;
	struct Uniform;
	using Uniforms = std::vector<Uniform>;

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
		std::unordered_map<Id, Uniforms> m_Shaders;

	};

}
