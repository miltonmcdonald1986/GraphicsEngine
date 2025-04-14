#include "pch.h"
#include "IEngine.h"
#include "Engine.h"

namespace GraphicsEngine
{

	auto CreateEngine() -> IEnginePtr
	{
		return IEnginePtr(new Engine());
	}

}
