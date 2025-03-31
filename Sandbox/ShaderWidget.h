#pragma once

#include "Header.h"
#include "Widget.h"

struct Uniform
{
	GLenum type = 0;
	std::string name;
};

class ShaderWidget : public Widget
{
public:
    ShaderWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<GraphicsEngine::Engine> spEngine);

    virtual auto Iterate() -> void override;

private:
	std::vector<Uniform> m_Uniforms;
};
