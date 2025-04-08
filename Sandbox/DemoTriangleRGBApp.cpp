#include "DemoTriangleRGBApp.h"

#include "GraphicsEngine/IEngine.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"
#include "ShaderWidget.h"

DemoTriangleRGBApp::DemoTriangleRGBApp(GLFWwindow* spWindow)
    : App(spWindow)
{
    geGenerateEntity_Triangle3DRGB(m_spEngine.get());

    m_Widgets.push_back(std::unique_ptr<BackgroundColorWidget>(new BackgroundColorWidget(spWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<PolygonModeWidget>(new PolygonModeWidget(spWindow, m_spEngine)));
}
