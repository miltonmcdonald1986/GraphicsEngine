#include "DemoTriangleApp.h"

#include "glm/vec3.hpp"

#include "IEngine.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow)
    : App(pWindow)
{
	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3( 0.5f, -0.5f, 0.f),
		glm::vec3( 0.f,   0.5f, 0.f)
	};

	auto spShader = m_spEngine->CreateNewShaderFromFiles("shaders/A0Pos3f.vert", "", "shaders/ColorIs008033.frag");

	//Attribute attrVertices(vertices);
	//auto spEntity = m_spEngine->AddNewEntity({ attrVertices }, spShader);


    // geGenerateEntity_Pos3f(m_spEngine.get(), sizeof(vertices), vertices);

    m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}
