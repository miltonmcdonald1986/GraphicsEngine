#pragma once

#include "Engine.h"

class DemoTriangleApp
{
public:
	DemoTriangleApp(GraphicsEngine::Engine& engine);
	void Render();

private:
	GraphicsEngine::Engine& m_Engine;
	unsigned int m_VAO = 0;
};
