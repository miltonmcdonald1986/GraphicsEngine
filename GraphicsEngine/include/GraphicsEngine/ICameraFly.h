#pragma once

#include "ICamera.h"
#include "DllImpExp.h"

namespace GraphicsEngine
{

	class ICameraFly : public ICamera
	{
	public:
		virtual ~ICameraFly() = default;
	};

	using ICameraFlyPtr = std::shared_ptr<ICameraFly>;
	GRAPHICSENGINE_API auto CreateCameraFly() -> ICameraFlyPtr;

}
