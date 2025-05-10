#pragma once

#include "App.h"
#include "fwd.h"
#include "GraphicsEngine/Types.h"

class DemoFlashingGreenTriangleApp : public App
{
public:
	explicit DemoFlashingGreenTriangleApp(GLFWwindow* pWindow);

	auto Iterate() -> void override;

private:

	GraphicsEngine::Types::StringView m_UniformName = "uGreenScalar";
};
