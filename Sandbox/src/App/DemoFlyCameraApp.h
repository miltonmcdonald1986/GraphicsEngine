#pragma once

#include "App.h"

#include "GLFW/glfw3.h"

class DemoFlyCameraApp : public App
{

public:

	explicit DemoFlyCameraApp(
		GLFWwindow* pWindow
	);

	~DemoFlyCameraApp(
	) override;

	auto Iterate(
	) -> void override;

private:

	GLFWscrollfun m_pPrevScrollCallback = nullptr;

};
