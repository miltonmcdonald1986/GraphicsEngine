#pragma once

#include "ShaderManager.h"

#include <memory>
#include <unordered_map>

#include "Fwd.h"
#include "Types.h"

namespace GraphicsEngine
{

	class ShaderManagerImpl : public ShaderManager
	{
	public:

		explicit ShaderManagerImpl(IEngine* pEngine);

		~ShaderManagerImpl() override = default;

		auto AddShader(
			const Path& vert,
			const Path& frag,
			const OptPath& oGeom
		) -> OptShaderId override;

		auto GetCurrentShader(
		) const->OptShaderId override;

		auto SetUniformData(
			ShaderId id,
			StringView name,
			const UniformData& data
		) -> bool override;

		auto UseShader(
			ShaderId id
		) const -> bool;

	private:

		auto AddShaderFromSource(
			StringView vert,
			StringView frag,
			OptStringView oGeom = std::nullopt
		) -> OptShaderId;

		IEngine* m_pEngine;
		std::unordered_map<Id, Uniforms> m_Shaders;

	};

	using ShaderManagerImplPtr = std::unique_ptr<ShaderManagerImpl>;
	auto CreateShaderManagerImpl(IEngine* pEngine) -> ShaderManagerImplPtr;

}
