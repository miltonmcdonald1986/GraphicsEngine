#pragma once

#include "ShaderManager.h"

#include <memory>
#include <unordered_map>

#include "Fwd.h"
#include "ShaderImpl.h"
#include "Types.h"

namespace GraphicsEngine
{

	class IEngine;

	class ShaderManagerImpl : public ShaderManager
	{
	public:

		explicit ShaderManagerImpl(IEngine* pEngine);

		~ShaderManagerImpl() override = default;

		auto AddShaderFromFiles (
			const Types::Path& vert,
			const Types::Path& frag,
			const Types::OptPath& oGeom
		) -> Shader* override;

		auto AddShaderFromSource (
			const Types::StringView& vert,
			const Types::StringView& frag,
			const Types::OptStringView& oGeom
		) -> Shader* override;

		auto GetCurrentShader () -> Shader* override;

		auto GetShader (Types::ShaderId id) -> Shader* override;

		IEngine* m_pEngine;
		std::unordered_map<Types::ShaderId, ShaderImpl> m_Shaders;

	};

	using ShaderManagerImplPtr = std::unique_ptr<ShaderManagerImpl>;
	auto CreateShaderManagerImpl(IEngine* pEngine) -> ShaderManagerImplPtr;

}
