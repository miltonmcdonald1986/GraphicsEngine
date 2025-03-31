#pragma once

#include "Widget.h"

#include <string>
#include <vector>

#include "glad/glad.h"

struct Uniform
{
	GLenum type = 0;
	std::string name;
};

class ShaderWidget : public Widget
{
public:
    ShaderWidget(GLFWwindowSharedPtr, GraphicsEngine::IEngineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:
	std::vector<Uniform> m_Uniforms;
};
