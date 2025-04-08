#pragma once

#include "Widget.h"

class MainMenuWidget : public Widget
{
public:
    MainMenuWidget(GLFWwindow* pWindow, GEengineSharedPtr spEngine, bool& appSelected, int& selectedItem);
    virtual auto Iterate() -> void override;

private:
    bool& m_AppSelected;
    int& m_SelectedItem;
};

