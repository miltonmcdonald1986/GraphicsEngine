#pragma once

#include "ICamera.h"
#include "DllImpExp.h"

namespace GraphicsEngine
{

	/// @brief A static camera that simply adjusts for window-resizing.
	class ICameraViewport : public ICamera
	{
	public:
		~ICameraViewport() override = default;
	};

	using ICameraViewportPtr = std::shared_ptr<ICameraViewport>;
	GRAPHICSENGINE_API auto CreateCameraViewport() -> ICameraViewportPtr;

}
