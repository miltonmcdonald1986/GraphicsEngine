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
	using IEntityPtr = std::shared_ptr<IEntity>;
	using IEntities = std::vector<IEntityPtr>;

	class ILog;
	using ILogPtr = std::shared_ptr<ILog>;
	
	class IShader;

	class ITexture;
	using ITexturePtr = std::shared_ptr<ITexture>;

	class IUniform;
	
	// Aliases

	using Count = int;
	using EntityId = unsigned int;
	using IAttributePtr = std::shared_ptr<IAttribute>;
	using IAttributes = std::vector<IAttributePtr>;
	using IEnginePtr = std::shared_ptr<IEngine>;	
	using Index = unsigned int;
	using Indices = std::vector<Index>;
	using IShaderPtr = std::shared_ptr<IShader>;
	using IShaders = std::vector<IShaderPtr>;
	using IUniformPtr = std::shared_ptr<IUniform>;
	using IUniforms = std::vector<IUniformPtr>;
	using Path = std::filesystem::path;
	using ShaderId = unsigned int;
	using String = std::string;
	using Strings = std::vector<String>;
	using UniformLocation = int;
	using VAO = unsigned int;

}
