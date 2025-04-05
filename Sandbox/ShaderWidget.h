#pragma once

#include "Widget.h"

#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/Uniform.h"

#include <string>
#include <vector>

class ShaderWidget : public Widget
{
public:
    ShaderWidget(GLFWwindowSharedPtr, GEengineSharedPtr spEngine);

    virtual auto Iterate() -> void override;

private:
	std::vector<GEuniform> m_Uniforms;
};
