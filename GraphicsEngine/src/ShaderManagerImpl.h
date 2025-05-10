#pragma once

#include "ShaderManager.h"

#include <memory>
#include <unordered_map>

#include "Fwd.h"
#include "Types.h"

namespace GraphicsEngine
{

	class IEngine;

	class ShaderManagerImpl : public ShaderManager
	{
	public:

		explicit ShaderManagerImpl(IEngine* pEngine);

		~ShaderManagerImpl() override = default;

		auto AddShader(
			const Types::Path& vert,
			const Types::Path& frag,
			const Types::OptPath& oGeom
		) -> Types::OptShaderId override;

		auto GetCurrentShader(
		) const->Types::OptShaderId override;

		auto SetUniformData(
			Types::ShaderId id,
			Types::StringView name,
			const Types::UniformData& data
		) -> bool override;

		auto UseShader(
			Types::ShaderId id
		) const -> bool;

	private:

		auto AddShaderFromSource(
			Types::StringView vert,
			Types::StringView frag,
			Types::OptStringView oGeom = std::nullopt
		) -> Types::OptShaderId;

		IEngine* m_pEngine;
		std::unordered_map<Types::Id, Uniforms> m_Shaders;

	};

	using ShaderManagerImplPtr = std::unique_ptr<ShaderManagerImpl>;
	auto CreateShaderManagerImpl(IEngine* pEngine) -> ShaderManagerImplPtr;

}
