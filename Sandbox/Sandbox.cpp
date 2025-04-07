#include <crtdbg.h>

#include "MainLoop.h"
#include "UI.h"
#include "Window.h"

int main()
{
    // Enable Memory Leak Detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto pWindow = InitializeGLFW();
    if (!pWindow)
        return -1;
    
    if (!InitializeDearImGui(pWindow))
    {
        TerminateGLFW(pWindow);
        return -1;
    }

    MainLoop(pWindow);

    TerminateDearImGui();
    TerminateGLFW(pWindow);
   
    return 0;
}

//int main(void)
//{
//    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//    _CrtSetBreakAlloc(171);
//
//    //glfwInit();
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    //GLFWwindow* pWindow = glfwCreateWindow(800, 600, "Graphics Engine Sandbox", NULL, NULL);
//
//    ///* Make the window's context current */
//    //glfwMakeContextCurrent(pWindow);
//    //glfwSetFramebufferSizeCallback(pWindow, OnFramebufferSize);
//
//    //glfwSwapInterval(1);
//
//    // gladLoadGL();
//
//    // Setup Dear ImGui context
//   // IMGUI_CHECKVERSION();
//   // ImGui::CreateContext();
//   // ImGuiIO& io = ImGui::GetIO();
//   // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//   // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
//   // // Setup Platform/Renderer backends
//   // ImGui_ImplGlfw_InitForOpenGL(pWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
//   // ImGui_ImplOpenGL3_Init();
//
//   // // Declare ImGui widgets
//   // io.Fonts->AddFontFromFileTTF("C:\\WINDOWS\\FONTS\\CASCADIAMONO.TTF", 18);
//
//   // /* Loop until the user closes the window */
//   // while (!glfwWindowShouldClose(pWindow))
//   // {       
//   //     static bool runMainMenu = true;
//   //     static int selectedItem = 0;
//   //     if (runMainMenu)
//   //     {
//   //         ImGui_ImplOpenGL3_NewFrame();
//   //         ImGui_ImplGlfw_NewFrame();
//   //         ImGui::NewFrame();
//
//   //         ImGui::OpenPopup("Main Menu");
//
//   //         // Ensure the popup fills the entire screen
//   //         ImVec2 displaySize = ImGui::GetIO().DisplaySize; // Get the size of the whole application window
//   //         ImGui::SetNextWindowSize(displaySize);
//   //         ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
//   //         if (ImGui::BeginPopupModal("Main Menu", nullptr, ImGuiWindowFlags_NoTitleBar))
//   //         {
//   //             // Calculate position to center the contents
//   //             ImVec2 contentSize = ImVec2(300, 200); // Define the size of your content
//   //             ImVec2 windowSize = ImGui::GetWindowSize();
//   //             ImVec2 centerPos = ImVec2((windowSize.x - contentSize.x) * 0.5f, (windowSize.y - contentSize.y) * 0.5f);
//
//   //             // Move the cursor to the calculated center position
//   //             ImGui::SetCursorPos(centerPos);
//
//   //             const size_t NUM_ITEMS = 4;
//   //             static const char* items[NUM_ITEMS] = { "Demo triangle", "Demo triangle RGB", "Demo indexed points", "Dear ImGui demo window" };
//
//   //             ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Graphics Engine Sandbox").x) * 0.5f);
//   //             ImGui::Text("Graphics Engine Sandbox");
//   //             ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Please make a selection").x) * 0.5f);
//   //             ImGui::Text("Please make a selection");
//   //             ImGui::SetNextWindowSize(ImVec2(400, NUM_ITEMS*ImGui::GetTextLineHeight() + 2*ImGui::GetStyle().ItemSpacing.y + 4*ImGui::GetStyle().FramePadding.y));
//   //             ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 400) * 0.5f);
//   //             ImGui::ListBox("##Items", &selectedItem, items, IM_ARRAYSIZE(items));
//   //             float windowWidth = ImGui::GetWindowSize().x;
//   //             float buttonWidth = 100.0f; // Set your button width
//   //             ImGui::SetCursorPosX((windowWidth - buttonWidth) * 0.5f);
//   //             if (ImGui::Button("Run", ImVec2(buttonWidth, 30.f)))
//   //             {
//   //                 ImGui::CloseCurrentPopup();
//   //                 runMainMenu = false;
//   //             }
//
//   //             ImGui::EndPopup();
//   //         }
//
//   //         ImGui::Render();
//   //         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//   //     }
//   //     else
//   //     {
//			//switch (selectedItem)
//			//{
//			//case 0:
//			//{
//			//	DemoTriangleApp app(pWindow);
//			//	app.Run();
//			//	break;
//			//}
//   //         case 1:
//   //         {
//   //             DemoTriangleRGBApp app(pWindow);
//   //             app.Run();
//   //             break;
//   //         }
//   //         case 2:
//   //         {
//   //             DemoIndexedPointsApp app(pWindow);
//   //             app.Run();
//   //             break;
//   //         }
//			//case 3:
//			//{
//			//	ImGuiDemoWindowApp app(pWindow);
//   //             app.Run();
//			//	break;
//			//}
//			//}
//
//   //         runMainMenu = true;
//   //     }
//
//   //     /* Swap front and back buffers */
//   //     glfwSwapBuffers(pWindow);
//
//   //     /* Poll for and process events */
//   //     glfwPollEvents();
//   // }
//
//   // ImGui_ImplOpenGL3_Shutdown();
//   // ImGui_ImplGlfw_Shutdown();
//   // ImGui::DestroyContext();
//
//    /*glfwDestroyWindow(pWindow);
//    glfwTerminate();*/
//
//    _CrtDumpMemoryLeaks();
//    return 0;
//}
