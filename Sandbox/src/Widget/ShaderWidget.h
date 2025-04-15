#pragma once

#include "Widget.h"

#include <string>
#include <vector>

class ShaderWidget : public Widget
{
public:
    ShaderWidget(GLFWwindow*, GraphicsEngine::IEnginePtr spEngine);

    virtual auto Iterate() -> void override;

private:
	std::vector<GraphicsEngine::IUniformPtr> m_Uniforms;
};
