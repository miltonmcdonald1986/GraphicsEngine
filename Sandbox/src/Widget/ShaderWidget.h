#pragma once

#include "fwd.h"
#include "Widget.h"

class ShaderWidget : public Widget
{
public:

	ShaderWidget (
		GLFWwindow* spWindow, 
		graphics_engine::IEnginePtr spEngine
	);

	~ShaderWidget () override = default;

	auto Iterate (bool* pShow = nullptr) -> void override;
};

using ShaderWidgetPtr = std::shared_ptr<ShaderWidget>;
auto CreateShaderWidget (GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine) -> ShaderWidgetPtr;
