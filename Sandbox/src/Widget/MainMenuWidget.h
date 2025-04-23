#pragma once

#include "Widget.h"

class MainMenuWidget : public Widget
{
public:
    MainMenuWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine, bool& appSelected, int& selectedItem);
    auto Iterate() -> void override;

private:
    bool& m_AppSelected;
    int& m_SelectedItem;
};

