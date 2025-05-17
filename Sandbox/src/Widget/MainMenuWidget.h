#pragma once

#include "Widget.h"

class MainMenuWidget : public Widget
{
public:
    MainMenuWidget(GLFWwindow* pWindow, graphics_engine::IEnginePtr spEngine, bool& appSelected, int& selectedItem);
    auto Iterate(bool* pShow) -> void override;

private:
    bool& m_AppSelected;
    int& m_SelectedItem;
};

