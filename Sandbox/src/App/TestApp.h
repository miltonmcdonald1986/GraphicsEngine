#pragma once

#include "App.h"

class TestApp : public App
{
public:
	explicit TestApp(GLFWwindow* pWindow);

private:
	GraphicsEngine::IEntityPtr m_spEntity = nullptr;
};
