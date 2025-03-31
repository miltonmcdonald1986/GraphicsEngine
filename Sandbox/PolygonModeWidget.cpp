#include "PolygonModeWidget.h"

#include <Windows.h>

#include "imgui.h"

#include "GraphicsEngine/GL.h"

using namespace GraphicsEngine;

PolygonModeWidget::PolygonModeWidget(std::shared_ptr<GLFWwindow> spWindow, IEngineSharedPtr spEngine)
    : Widget(spWindow, spEngine)
{
    GLint param[2];
    glGetIntegerv(GL_POLYGON_MODE, param);
    
    if (param[0] == GL_POINT)
        m_Mode = 0;
    if (param[0] == GL_LINE)
        m_Mode = 1;
    if (param[0] == GL_FILL)
        m_Mode = 2;
}

void PolygonModeWidget::Iterate()
{
    auto UpdatePolygonMode = [](int mode)
    {
        int modeGl;
        switch (mode)
        {
        case 0:
            modeGl = GL_POINT;
            break;
        case 1:
            modeGl = GL_LINE;
            break;
        case 2:
            modeGl = GL_FILL;
            break;
        }
        
        glPolygonMode(GL_FRONT_AND_BACK, static_cast<GLenum>(modeGl));
        GL_ERROR();
    };

    ImGui::Begin("Polygon Mode", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    if (ImGui::RadioButton("Point", &m_Mode, 0))
        UpdatePolygonMode(m_Mode);
    ImGui::SameLine();
    if (ImGui::RadioButton("Line", &m_Mode, 1))
        UpdatePolygonMode(m_Mode);
    ImGui::SameLine();
    if (ImGui::RadioButton("Fill", &m_Mode, 2))
        UpdatePolygonMode(m_Mode);
    ImGui::End();
}
