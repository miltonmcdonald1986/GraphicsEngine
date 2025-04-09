#include "DemoTriangleApp.h"

#include "IEngine.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    geGenerateEntity_Triangle3DBasic(m_spEngine.get());

    m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}
