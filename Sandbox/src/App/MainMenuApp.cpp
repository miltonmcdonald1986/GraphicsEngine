#include "MainMenuApp.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "IEngine.h"

#include "MainMenuWidget.h"

namespace
{

    auto OnKey(GLFWwindow* pWindow, int key, int /*scancode*/, int action, int /*mods*/) -> void
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
    }

}

MainMenuApp::MainMenuApp(GLFWwindow* pWindow)
	: App(pWindow)
{
    m_MainMenuPrevUserPointer = glfwGetWindowUserPointer(m_pWindow);
    glfwSetWindowUserPointer(m_pWindow, GetUserDataPointer());

    m_MainMenuPrevKeyCallback = glfwSetKeyCallback(m_pWindow, OnKey);

	m_Widgets.push_back(WidgetUniquePointer(new MainMenuWidget(pWindow, m_spEngine, m_AppSelected, m_SelectedItem)));
}

MainMenuApp::~MainMenuApp()
{
    glfwSetWindowUserPointer(m_pWindow, m_MainMenuPrevUserPointer);
    glfwSetKeyCallback(m_pWindow, m_MainMenuPrevKeyCallback);
}

auto MainMenuApp::GetResults() -> std::pair<Result_AppWasSelected, Result_SelectedItem>
{
	return std::make_pair(m_AppSelected, m_SelectedItem);
}

auto MainMenuApp::Run() -> void
{
    while (m_Running)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        m_spEngine->Render();

        IterateWidgets();
        if (m_AppSelected)
            m_Running = false;

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();

        m_Running = (m_Running && !glfwWindowShouldClose(m_pWindow));
    }
}
