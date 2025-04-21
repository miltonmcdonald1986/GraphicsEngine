#include "DemoTexturesCombinedApp.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "GraphicsEngine/IAttribute.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IEntity.h"
#include "GraphicsEngine/IShader.h"
#include "GraphicsEngine/IUniform.h"

#include "BackgroundColorWidget.h"
#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"
#include "ShaderWidget.h"

DemoTexturesCombinedApp::DemoTexturesCombinedApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });

	std::vector<glm::vec3> vertices =
	{
		glm::vec3(-0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.f),
		glm::vec3(0.5f, 0.5f, 0.f),
		glm::vec3(-0.5f, 0.5f, 0.f)
	};

	std::vector<glm::vec2> texCoords =
	{
		glm::vec2(0.f, 0.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(0.f, 1.f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0
	};

	auto spEntity = m_spEngine->CreateNewEntity({ GraphicsEngine::CreateAttribute(vertices), GraphicsEngine::CreateAttribute(texCoords) }, indices);
	auto spShader = m_spEngine->CreateNewShaderFromFiles("shaders/DemoTexturesCombined.vert", "", "shaders/DemoTexturesCombined.frag");
    spEntity->SetShader(spShader);
	spEntity->SetTextures({ 
        m_spEngine->CreateNewTextureFromFile("uTextureContainer", "textures/container.jpg"),
        m_spEngine->CreateNewTextureFromFile("uTextureAwesomeFace", "textures/awesomeface.png")
        });

    if (spShader)
        {
            auto spUniform = spShader->GetActiveUniform("uMix");
            if (spUniform)
                spUniform->SetData(0.2f);
        }

	m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new EngineLogWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
    m_Widgets.push_back(std::unique_ptr<Widget>(new ShaderWidget(m_pWindow, m_spEngine)));
}
