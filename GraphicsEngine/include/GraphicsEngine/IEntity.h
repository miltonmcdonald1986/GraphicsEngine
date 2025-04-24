#pragma once

#include "IShader.h"
#include "ITexture.h"

namespace GraphicsEngine
{

	class IEntity
	{
	public:
		virtual ~IEntity() = default;

		virtual auto GetId() const -> unsigned int = 0;
		virtual auto GetModelMatrix() const -> glm::mat4 = 0;
		virtual auto GetNumIndices() const -> int = 0;
		virtual auto GetNumVertices() const -> int = 0;
		virtual auto GetShader() const -> IShaderPtr = 0;
		virtual auto GetTextures() const -> ITextures = 0;
		virtual auto GetVAO() const -> unsigned int = 0;
		virtual auto SetModelMatrix(const glm::mat4& model) -> void = 0;
		virtual auto SetShader(IShaderPtr spShader) -> void = 0;
		virtual auto SetTextures(const ITextures& textures) -> void = 0;
	};

	using IEntityPtr = std::shared_ptr<IEntity>;
	using IEntities = std::vector<IEntityPtr>;

}
