#pragma once

#include <memory>

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine
{

	class IEngine
	{
	};

	using IEngineSharedPtr = std::shared_ptr<IEngine>;
	auto GRAPHICSENGINE_API CreateEngine() -> IEngineSharedPtr;

}
