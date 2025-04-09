#include "EngineLogWidget.h"

#include <algorithm>
#include <format>

#include "imgui.h"

EngineLogWidget::EngineLogWidget(GLFWwindow* pWindow, GEengineSharedPtr spEngine)
    : Widget(pWindow, spEngine)
{
    m_LogLevel = geGetLogLevel();
}

auto EngineLogWidget::Iterate() -> void
{
    bool update = false;

    auto windowSize = ImGui::GetIO().DisplaySize;
    ImGui::SetNextWindowSize(ImVec2(windowSize.x, 0.25f*windowSize.y), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0.75f*windowSize.y), ImGuiCond_Once);
    ImGui::Begin("Graphics Engine Log");
    ImGui::Text("Log Level");
    if (ImGui::RadioButton("Trace", &m_LogLevel, GE_LOG_LEVEL_TRACE))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Debug", &m_LogLevel, GE_LOG_LEVEL_DEBUG))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Info", &m_LogLevel, GE_LOG_LEVEL_INFO))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Warn", &m_LogLevel, GE_LOG_LEVEL_WARN))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Error", &m_LogLevel, GE_LOG_LEVEL_ERR))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Critical", &m_LogLevel, GE_LOG_LEVEL_CRITICAL))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Off", &m_LogLevel, GE_LOG_LEVEL_OFF))
        update = true;

    if (update)
        geSetLogLevel(static_cast<GElogLevel>(m_LogLevel));

    int numMessages = 0;
    const char** messages = nullptr;
    geGetRecentLogMessages(m_spEngine.get(), &numMessages, &messages);
    
    if (numMessages == 0)
        ImGui::Text("Log is empty.");
    else
        ImGui::Text(std::format("Showing {} messages.", numMessages).c_str());

    std::reverse(messages, messages + numMessages);
    for (int i = 0; i < numMessages; ++i)
        ImGui::Text(messages[i]);
    ImGui::End();
}
