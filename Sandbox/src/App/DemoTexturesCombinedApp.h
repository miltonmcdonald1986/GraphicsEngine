#pragma once

#include "App.h"

class DemoTexturesCombinedApp : public App
{
public:
	explicit DemoTexturesCombinedApp(GLFWwindow* pWindow);
	auto Iterate() -> void override;

private:
	GraphicsEngine::IEntityPtr m_spEntity = nullptr;
};
