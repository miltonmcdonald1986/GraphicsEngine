#include <string>

#include <ShObjIdl_core.h>

#include "GraphicsEngine/Shader.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/GL.h"

#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "BackgroundColorWidget.h"
#include "DemoTriangleApp.h"
#include "DemoTriangleRGBApp.h"
#include "DemoIndexedPointsApp.h"
#include "ImGuiDemoWindowApp.h"

using namespace GraphicsEngine;

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

void OnFramebufferSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    auto CreateGLFWWindow = [](int width, int height, const char* title) -> std::shared_ptr<GLFWwindow>
        {
            if (!glfwInit())
                return nullptr;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            std::shared_ptr<GLFWwindow> spWindow = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, "Hello World", NULL, NULL), [](GLFWwindow* pWindow) {
                glfwDestroyWindow(pWindow);
                glfwTerminate();
                });

            return spWindow;
        };

    auto spWindow = CreateGLFWWindow(800, 600, "Graphics Engine Sandbox");
    if (!spWindow)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(spWindow.get());
    glfwSetFramebufferSizeCallback(spWindow.get(), OnFramebufferSize);

    glfwSwapInterval(1);

    // gladLoadGL();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(spWindow.get(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Declare ImGui widgets
    io.Fonts->AddFontFromFileTTF("C:\\WINDOWS\\FONTS\\CASCADIAMONO.TTF", 18);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(spWindow.get()))
    {       
        static bool runMainMenu = true;
        static int selectedItem = 0;
        if (runMainMenu)
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::OpenPopup("Main Menu");

            // Ensure the popup fills the entire screen
            ImVec2 displaySize = ImGui::GetIO().DisplaySize; // Get the size of the whole application window
            ImGui::SetNextWindowSize(displaySize);
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            if (ImGui::BeginPopupModal("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar))
            {
                // Calculate position to center the contents
                ImVec2 contentSize = ImVec2(300, 200); // Define the size of your content
                ImVec2 windowSize = ImGui::GetWindowSize();
                ImVec2 centerPos = ImVec2((windowSize.x - contentSize.x) * 0.5f, (windowSize.y - contentSize.y) * 0.5f);

                // Move the cursor to the calculated center position
                ImGui::SetCursorPos(centerPos);

                const size_t NUM_ITEMS = 4;
                static const char* items[NUM_ITEMS] = { "Demo triangle", "Demo triangle RGB", "Demo indexed points", "Dear ImGui demo window" };

                ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Graphics Engine Sandbox").x) * 0.5f);
                ImGui::Text("Graphics Engine Sandbox");
                ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Please make a selection").x) * 0.5f);
                ImGui::Text("Please make a selection");
                ImGui::SetNextWindowSize(ImVec2(400, NUM_ITEMS*ImGui::GetTextLineHeight() + 2*ImGui::GetStyle().ItemSpacing.y + 4*ImGui::GetStyle().FramePadding.y));
                ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 400) * 0.5f);
                ImGui::ListBox("##Items", &selectedItem, items, IM_ARRAYSIZE(items));
                float windowWidth = ImGui::GetWindowSize().x;
                float buttonWidth = 100.0f; // Set your button width
                ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
                if (ImGui::Button("Run", ImVec2(buttonWidth, 30.f)))
                {
                    ImGui::CloseCurrentPopup();
                    runMainMenu = false;
                }

                ImGui::EndPopup();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        else
        {
			switch (selectedItem)
			{
			case 0:
			{
				DemoTriangleApp app(spWindow);
				app.Run();
				break;
			}
            case 1:
            {
                DemoTriangleRGBApp app(spWindow);
                app.Run();
                break;
            }
            case 2:
            {
                DemoIndexedPointsApp app(spWindow);
                app.Run();
                break;
            }
			case 3:
			{
				ImGuiDemoWindowApp app(spWindow);
                app.Run();
				break;
			}
			}

            runMainMenu = true;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(spWindow.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
