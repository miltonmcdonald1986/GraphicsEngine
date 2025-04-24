#pragma once

#include "App.h"

class DemoCoordinateSystemsDepthApp : public App
{
public:
	explicit DemoCoordinateSystemsDepthApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;

private:
	GraphicsEngine::IEntityPtr m_spEntity = nullptr;
};
