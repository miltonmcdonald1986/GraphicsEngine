#include "MainLoop.h"
#include "UI.h"
#include "Window.h"

int main()
{
#ifdef _WIN32
    // Enable Memory Leak Detection
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

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
