#include "MainMenuApp.h"

#include "GraphicsEngine/IEngine.h"

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
	: App(pWindow),
      m_MainMenuPrevUserPointer(glfwGetWindowUserPointer(pWindow)),
      m_MainMenuPrevKeyCallback(glfwSetKeyCallback(pWindow, OnKey))
{
    glfwSetWindowUserPointer(pWindow, App::GetUserDataPointer());
	GetWidgets().push_back(std::make_unique<MainMenuWidget>(pWindow, GetEngine(), m_AppSelected, m_SelectedItem));
}

MainMenuApp::~MainMenuApp()
{
    auto pWindow = GetWindow();
    glfwSetWindowUserPointer(pWindow, m_MainMenuPrevUserPointer);
    glfwSetKeyCallback(pWindow, m_MainMenuPrevKeyCallback);
}

auto MainMenuApp::GetResults() -> std::pair<Result_AppWasSelected, Result_SelectedItem>
{
	return std::make_pair(m_AppSelected, m_SelectedItem);
}

auto MainMenuApp::Run() -> void
{
    while (GetIsRunning())
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        GetEngine()->Render();

        IterateWidgets();
        if (m_AppSelected)
            SetIsRunning(false);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        auto pWindow = GetWindow();

        glfwSwapBuffers(pWindow);
        glfwPollEvents();

        SetIsRunning(GetIsRunning() && !glfwWindowShouldClose(pWindow));
    }
}
