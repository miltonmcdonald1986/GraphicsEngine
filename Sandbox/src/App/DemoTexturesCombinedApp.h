#pragma once

#include "App.h"

class DemoTexturesCombinedApp : public App
{
public:
	explicit DemoTexturesCombinedApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;

private:
	graphics_engine::entities::Entity* m_pEntity = nullptr;
};
