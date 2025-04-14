#include "DemoFlashingGreenTriangleApp.h"

#include "IEngine.h"
#include "IShader.h"

#include "BackgroundColorWidget.h"
#include "PolygonModeWidget.h"

DemoFlashingGreenTriangleApp::DemoFlashingGreenTriangleApp(GLFWwindow* pWindow)
	: App(pWindow)
{
	float vertices[] =
	{
		-0.5f, -0.5f, 0.f,
		 0.5f, -0.5f, 0.f,
		 0.f,   0.5f, 0.f
	};
	// auto entId = geGenerateEntity_Pos3f(m_spEngine.get(), sizeof(vertices), vertices);
	// GEshader* pShader = geCreateShaderFromFiles("shaders/A0Pos3f.vert", nullptr, "shaders/GreenScalar.frag");
	// geSetEntityShader(m_spEngine.get(), entId, pShader);
	
	// std::vector<GEuniform> uniforms(geGetNumActiveUniforms(pShader));
	// geGetActiveUniforms(pShader, uniforms.data());

	// There should be one uniform called 'uGreenScalar'
	//uniform->m_Data.u_float = 1.f;
	//geSetUniform(pShader, uniform);

	m_Widgets.push_back(std::unique_ptr<Widget>(new BackgroundColorWidget(m_pWindow, m_spEngine)));
	m_Widgets.push_back(std::unique_ptr<Widget>(new PolygonModeWidget(m_pWindow, m_spEngine)));
}
