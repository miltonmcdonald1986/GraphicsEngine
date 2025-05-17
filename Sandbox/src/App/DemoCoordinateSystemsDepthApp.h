#pragma once

#include "App.h"

class DemoCoordinateSystemsDepthApp : public App
{
public:
	explicit DemoCoordinateSystemsDepthApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;

private:
	graphics_engine::entities::Entity* m_pEntity = nullptr;
};
