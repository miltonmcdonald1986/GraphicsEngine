#pragma once

#include "Widget.h"

class DearImGuiDemoWindowWidget : public Widget
{
public:
    DearImGuiDemoWindowWidget(GLFWwindow* pWindow, GEengineSharedPtr spEngine);
    virtual auto Iterate() -> void override;
};
