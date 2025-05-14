#include "App.h"

#include "GraphicsEngine/IEngine.h"

#include "EngineLogWidget.h"
#include "PolygonModeWidget.h"
#include "ShaderWidget.h"
#include "Widget.h"

namespace AppCallbacks
{

    void OnFramebufferSize(GLFWwindow* pWindow, int newWidth, int newHeight)
    {
        if (!pWindow)
            return;

        auto pApp = static_cast<App*>(glfwGetWindowUserPointer(pWindow));
        if (!pApp)
            return;

        auto spEngine = pApp->GetEngine();
        if (!spEngine)
            return;

        // Tell the engine that the viewport was resized
        spEngine->ResizeViewport(newWidth, newHeight);

        pApp->Iterate ();
    }

    auto OnKey(GLFWwindow* pWindow, int key, int scancode, int action, int mods) -> void
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            auto pApp = reinterpret_cast<App*>(glfwGetWindowUserPointer(pWindow));  //NOSONAR: GLFW provides a void*, there's nothing I can do about that.
            if (pApp)
                pApp->SetIsRunning(false);
        }
        else
            ImGui_ImplGlfw_KeyCallback(pWindow, key, scancode, action, mods);
    }

}

App::App(GLFWwindow* pWindow)
    :   m_pPrevFramebufferSizeCallback(glfwSetFramebufferSizeCallback (pWindow, AppCallbacks::OnFramebufferSize)),
        m_pWindow(pWindow),
	    m_spEngine(GraphicsEngine::CreateEngine())
{
    m_PrevUserPointer = glfwGetWindowUserPointer(m_pWindow);
    glfwSetWindowUserPointer(m_pWindow, this);

    m_PrevKeyCallback = glfwSetKeyCallback(m_pWindow, AppCallbacks::OnKey);

    m_spWidgetEngineLog = CreateEngineLogWidget(m_pWindow, m_spEngine);
    m_spWidgetPolygonMode = CreatePolygonModeWidget(m_pWindow, m_spEngine);
    m_spWidgetShader = CreateShaderWidget (m_pWindow, m_spEngine);
}

App::~App()
{
    glfwSetFramebufferSizeCallback(GetWindow(), m_pPrevFramebufferSizeCallback);
    glfwSetKeyCallback(m_pWindow, m_PrevKeyCallback);
    glfwSetWindowUserPointer(m_pWindow, m_PrevUserPointer);
}

auto App::Iterate() -> void
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderDockSpace();

    if (m_spEngine)
        m_spEngine->Render();

    IterateWidgets();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();

    m_Running = (m_Running && !glfwWindowShouldClose(m_pWindow));
}

auto App::RenderDockSpace() -> void
{
    // Get the size of the full GLFW window
    int window_width;
    int window_height;
    glfwGetWindowSize(m_pWindow, &window_width, &window_height);

    // Create a fullscreen, borderless docking space
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)window_width, (float)window_height));
    ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("DockSpace Window", nullptr, window_flags);

    // Create the dockspace ID and enable docking
    ImGuiID dockspace_id = ImGui::GetID("MyFullscreenDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();
}

auto App::Run() -> void
{
    while (m_Running)
    {
        Iterate();
    }
}

auto App::IterateWidgets() -> void
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::GetIO().KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_L))
            m_ShowEngineLogWidget = !m_ShowEngineLogWidget;

        if (ImGui::BeginMenu("Widgets"))
        {
            if (ImGui::MenuItem("Engine Log", "Ctrl+L"))
                m_ShowEngineLogWidget = true;

            if (ImGui::MenuItem("Polygon Mode"))
                m_ShowPolygonModeWidget = true;

            if (ImGui::MenuItem ("Shader"))
                m_ShowShaderWidget = true;

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (m_ShowEngineLogWidget)
        m_spWidgetEngineLog->Iterate(&m_ShowEngineLogWidget);
    if (m_ShowPolygonModeWidget)
        m_spWidgetPolygonMode->Iterate(&m_ShowPolygonModeWidget);
    if (m_ShowShaderWidget)
        m_spWidgetShader->Iterate (&m_ShowShaderWidget);

	for (const auto& upWidget : m_Widgets)
	{
		upWidget->Iterate(nullptr);
	}
}

auto App::SetIsRunning(bool isRunning) -> void
{
    m_Running = isRunning;
}

auto App::GetEngine() const -> GraphicsEngine::IEnginePtr
{
    return m_spEngine;
}

auto App::GetIsRunning() const -> bool
{
    return m_Running;
}

auto App::GetWidgets() -> Widgets&
{
    return m_Widgets;
}

auto App::GetWindow() const -> GLFWwindow *
{
    return m_pWindow;
}
