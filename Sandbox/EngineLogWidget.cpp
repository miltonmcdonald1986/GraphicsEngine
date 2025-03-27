#include "EngineLogWidget.h"

#include "imgui.h"

using namespace GraphicsEngine;

EngineLogWidget::EngineLogWidget(std::shared_ptr<GLFWwindow> spWindow, std::shared_ptr<Engine> spEngine)
    : Widget(spWindow, spEngine)
{
    auto optLevel = Log::GetLevel();
    if (optLevel)
        m_LogLevel = static_cast<int>(*optLevel);
}

auto EngineLogWidget::Iterate() -> void
{
    bool update = false;

    ImGui::Begin("Graphics Engine Log");
    ImGui::Text("Log Level");
    if (ImGui::RadioButton("Trace", &m_LogLevel, 0))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Debug", &m_LogLevel, 1))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Info", &m_LogLevel, 2))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Warn", &m_LogLevel, 3))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Error", &m_LogLevel, 4))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Critical", &m_LogLevel, 5))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Off", &m_LogLevel, 6))
        update = true;

    if (update)
        Log::SetLevel(static_cast<Log::LogLevel>(m_LogLevel));

    auto msgs = Log::GetRecentLogMessages();

    if (msgs.empty())
        ImGui::Text("Log is empty.");
    else
        ImGui::Text(std::format("Showing {} messages.", msgs.size()).c_str());

    std::reverse(msgs.begin(), msgs.end());
    for (auto msg : msgs)
        ImGui::Text(msg.c_str());
    ImGui::End();
}
