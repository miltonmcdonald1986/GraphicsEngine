#pragma once

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	enum class EntityType;

	class IEngine
	{
	public:
		virtual ~IEngine() = default;
		virtual auto GenerateEntity(EntityType type) -> unsigned int = 0;
		virtual auto Render() const -> void = 0;
	};

	using IEngineSharedPtr = std::shared_ptr<IEngine>;
	auto GRAPHICSENGINE_API CreateEngine() -> IEngineSharedPtr;

}
