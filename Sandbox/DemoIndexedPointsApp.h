#pragma once

#include "App.h"

class DemoIndexedPointsApp : public App
{
public:

	DemoIndexedPointsApp(GLFWwindowSharedPtr spWindow, GraphicsEngine::IEngineSharedPtr spEngine);

	virtual auto Run() -> void override;

private:

	void Render() const;

	std::vector<unsigned int> m_Indices;
	unsigned int m_VAO = 0;
};
