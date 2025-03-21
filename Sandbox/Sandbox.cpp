#include <array>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <windows.h>
#include <ShObjIdl_core.h>

#include "Engine.h"
#include "ShaderUtilities.h"

std::string PWSTRToString(PWSTR wideStr) {
    if (!wideStr) {
        return std::string(); // Return an empty string if the input is null
    }

    // Determine the size of the resulting string
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);

    // Allocate buffer for the converted string
    std::string result(bufferSize, '\0');

    // Perform the conversion
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, &result[0], bufferSize, nullptr, nullptr);

    // Remove the trailing null character added by WideCharToMultiByte
    result.resize(bufferSize - 1);

    return result;
}

std::string OpenFileDialogBox()
{
    std::string filename;

    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        filename = PWSTRToString(pszFilePath);
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }

    return filename;
}

class BackgroundColorWidget
{
public:
    BackgroundColorWidget(GraphicsEngine::Engine& engine)
        : m_Engine(engine)
    {
        auto optBackgroundColor = engine.GetBackgroundColor();
        if (optBackgroundColor)
            std::copy(**optBackgroundColor, **optBackgroundColor + 4, m_Color);
    }

    void Iterate()
    {
        ImGui::Begin("Background Color", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        if (ImGui::ColorEdit4("MyColor##2f", m_Color, ImGuiColorEditFlags_Float))
            m_Engine.SetBackgroundColor(GraphicsEngine::Color(m_Color));

        ImGui::End();
    }

private:
    GraphicsEngine::Engine& m_Engine;
    float m_Color[4] = { 0.f, 0.f, 0.f, 1.f };
};

class CompileShaderWidget
{
public:
    CompileShaderWidget(GraphicsEngine::Engine& engine)
        : m_Engine(engine)
    {
        std::fill(m_FilenameVS, m_FilenameVS + MAX_PATH, '\0');
        std::fill(m_FilenameFS, m_FilenameFS + MAX_PATH, '\0');
    }

    void Iterate()
    {
        ImGui::Begin("Compile Shaders");
        ImGui::Text("Vertex Shader Filename");
        ImGui::SameLine();
        ImGui::InputText("##VS", m_FilenameVS, MAX_PATH);
        ImGui::SameLine();
        if (ImGui::Button("...##VS"))
        {
            std::string str = OpenFileDialogBox();
            std::copy(str.begin(), str.end(), m_FilenameVS);
        }
        ImGui::SameLine();
        if (ImGui::Button("Compile##VS"))
        {
            if (auto optId = GraphicsEngine::ShaderUtilities::CompileVertexShader(std::filesystem::path(m_FilenameVS)))
                m_VertexShader = *optId;
        }

        ImGui::Text("Fragment Shader Filename");
        ImGui::SameLine();
        ImGui::InputText("##FS", m_FilenameFS, MAX_PATH);
        ImGui::SameLine();
        if (ImGui::Button("...##FS"))
        {
            std::string str = OpenFileDialogBox();
            std::copy(str.begin(), str.end(), m_FilenameFS);
        }
        ImGui::SameLine();
        if (ImGui::Button("Compile##FS"))
        {
            if (auto optId = GraphicsEngine::ShaderUtilities::CompileFragmentShader(std::filesystem::path(m_FilenameFS)))
                m_FragmentShader = *optId;
        }

        ImGui::Text("Vertex Shader Id:");
        ImGui::SameLine();
        ImGui::Text(std::format("{}", m_VertexShader).c_str());
        ImGui::SameLine();
        ImGui::Dummy(ImVec2(50.f, 0));
        ImGui::SameLine();
        ImGui::Text("Fragment Shader Id:");
        ImGui::SameLine();
        ImGui::Text(std::format("{}", m_FragmentShader).c_str());
        ImGui::SameLine();
        ImGui::Dummy(ImVec2(50.f, 0));
        ImGui::SameLine();
        ImGui::Text("Program Id:");
        ImGui::SameLine();
        ImGui::Text(std::format("{}", m_Program).c_str());
        ImGui::SameLine();
        ImGui::Dummy(ImVec2(100.f, 0));
        ImGui::SameLine();
        if (ImGui::Button("Link Program"))
        {
            if (auto optId = GraphicsEngine::ShaderUtilities::LinkProgram({ m_VertexShader, m_FragmentShader }))
                m_Program = *optId;

            if (auto optResultVS = GraphicsEngine::ShaderUtilities::ShaderIsDeleted(m_VertexShader); optResultVS && *optResultVS)
                m_VertexShader = 0;

            if (auto optResultFS = GraphicsEngine::ShaderUtilities::ShaderIsDeleted(m_FragmentShader); optResultFS && *optResultFS)
                m_FragmentShader = 0;
        }
        ImGui::End();
    }

private:
    GraphicsEngine::Engine& m_Engine;
    GLuint m_VertexShader = 0;
    GLuint m_FragmentShader = 0;
    GLuint m_Program = 0;
    char m_FilenameVS[MAX_PATH];
    char m_FilenameFS[MAX_PATH];
};

class EngineLogWidget
{
public:
    EngineLogWidget(GraphicsEngine::Engine& engine)
        : m_Engine(engine)
    {
    }

    void Iterate()
    {
        ImGui::Begin("Engine Log");
        auto msgs = m_Engine.GetLatestLogMessages();
        std::reverse(msgs.begin(), msgs.end());
        for (auto msg : msgs)
            ImGui::Text(msg.c_str());
        ImGui::End();
    }

private:
    GraphicsEngine::Engine& m_Engine;
};

void OnFramebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int windowWidthInitial = 800;
    const int windowHeightInitial = 600;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidthInitial, windowHeightInitial, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSize);

    gladLoadGL();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    GraphicsEngine::Engine engine;
    
    GraphicsEngine::Color backgroundColor(0.2f, 0.3f, 0.3f, 1.f);
    engine.SetBackgroundColor(backgroundColor);

    // Declare ImGui widgets
    BackgroundColorWidget backgroundColorWidget(engine);
    CompileShaderWidget compileShaderWidget(engine);
    EngineLogWidget engineLogWidget(engine);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        backgroundColorWidget.Iterate();
        compileShaderWidget.Iterate();
        engineLogWidget.Iterate();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}

