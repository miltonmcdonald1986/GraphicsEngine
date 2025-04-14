#pragma once

#include "Widget.h"

#include "Uniform.h"

#include <string>
#include <vector>

class ShaderWidget : public Widget
{
public:
    ShaderWidget(GLFWwindow*, GraphicsEngine::IEnginePtr spEngine);

    virtual auto Iterate() -> void override;

private:
	std::vector<GEuniform> m_Uniforms;
};
