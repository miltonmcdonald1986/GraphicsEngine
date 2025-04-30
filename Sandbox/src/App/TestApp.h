#pragma once

#include "App.h"

class TestApp : public App
{
public:
	explicit TestApp(GLFWwindow* pWindow);
	~TestApp() override;
	auto Iterate() -> void override;

private:
	GLFWscrollfun m_pPrevScrollCallback = nullptr;
};
