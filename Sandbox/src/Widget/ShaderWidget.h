#pragma once

#include "Widget.h"
#include "fwd.h"

class ShaderWidget : public Widget
{
public:
    ShaderWidget(GLFWwindow*, GraphicsEngine::IEnginePtr spEngine);
	auto Iterate() -> void override;

private:
	std::vector<GraphicsEngine::IUniformPtr> m_Uniforms;
};
