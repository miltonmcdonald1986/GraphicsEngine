#pragma once

#include <memory>
#include <vector>

namespace GraphicsEngine
{

	class IEngine;
	using IEnginePtr = std::shared_ptr<IEngine>;

	class IShader;
	using IShaderPtr = std::shared_ptr<IShader>;
	using IShaders = std::vector<IShaderPtr>;

	class IUniform;
	using IUniformPtr = std::shared_ptr<IUniform>;
	using IUniforms = std::vector<IUniformPtr>;

}
