#pragma once

#include <filesystem>
#include <memory>
#include <vector>

namespace GraphicsEngine
{

	// Forward declarations

	class IAttribute;
	class IEngine;
	class IEntity;
	class IShader;
	class IUniform;
	
	// Aliases

	using IAttributePtr = std::shared_ptr<IAttribute>;
	using IAttributes = std::vector<IAttributePtr>;

	using IEnginePtr = std::shared_ptr<IEngine>;

	using IEntityPtr = std::shared_ptr<IEntity>;
	using IEntities = std::vector<IEntityPtr>;

	using Index = unsigned int;
	using Indices = std::vector<Index>;

	using IShaderPtr = std::shared_ptr<IShader>;
	using IShaders = std::vector<IShaderPtr>;

	using IUniformPtr = std::shared_ptr<IUniform>;
	using IUniforms = std::vector<IUniformPtr>;

	using Path = std::filesystem::path;

}
