#pragma once

#include "Widget.h"

#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/Uniform.h"

#include <string>
#include <vector>

class ShaderWidget : public Widget
{
public:
    ShaderWidget(GLFWwindowSharedPtr, GraphicsEngine::IEngineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:
	std::vector<GraphicsEngine::Uniform> m_Uniforms;
};
