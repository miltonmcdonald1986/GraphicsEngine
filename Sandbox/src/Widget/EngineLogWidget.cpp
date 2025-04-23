#include "EngineLogWidget.h"

#include "GraphicsEngine/IEngine.h"

EngineLogWidget::EngineLogWidget(GLFWwindow* pWindow, GraphicsEngine::IEnginePtr spEngine)
    : Widget(pWindow, spEngine),
      m_spLog(spEngine->GetLog())
{
}

auto EngineLogWidget::Iterate() -> void
{
    using namespace GraphicsEngine;

    bool update = false;

    m_LogLevel = std::to_underlying(m_spLog->GetLevel());

    ImGui::Begin("Graphics Engine Log");
    if (ImGui::Button("Clear Log"))
        m_spLog->ClearMessages();
    ImGui::Text("Log Level");
    if (ImGui::RadioButton("Trace", &m_LogLevel, static_cast<int>(LogLevel::Trace)))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Debug", &m_LogLevel, static_cast<int>(LogLevel::Debug)))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Info", &m_LogLevel, static_cast<int>(LogLevel::Info)))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Warn", &m_LogLevel, static_cast<int>(LogLevel::Warn)))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Error", &m_LogLevel, static_cast<int>(LogLevel::Error)))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Critical", &m_LogLevel, static_cast<int>(LogLevel::Critical)))
        update = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("Off", &m_LogLevel, static_cast<int>(LogLevel::Off)))
        update = true;

    if (update)
        m_spLog->SetLevel(static_cast<LogLevel>(m_LogLevel));

    auto messages = m_spLog->GetLatestMessages();
    if (messages.empty())
        ImGui::Text("Log is empty.");
    else
        ImGui::Text("%s", std::format("Showing {} messages.", messages.size()).c_str());

    ImGui::BeginChild("Messages", ImVec2(0, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
    std::ranges::reverse(messages);
    for (const auto& message : messages)
    {
        std::string messageStr(message);
        if (message.contains("[trace]"))
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.f), "%s", messageStr.c_str());
        else if (message.contains("[debug]"))
            ImGui::TextColored(ImVec4(0.f, 1.f, 1.f, 1.f), "%s", messageStr.c_str());
        else if (message.contains("[info]"))
            ImGui::TextColored(ImVec4(0.f, 1.f, 0.f, 1.f), "%s", messageStr.c_str());
        else if (message.contains("[warning]"))
            ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%s", messageStr.c_str());
        else if (message.contains("[error]"))
            ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "%s", messageStr.c_str());
        else if (message.contains("[critical]"))
            ImGui::TextColored(ImVec4(1.f, 0.f, 1.f, 1.f), "%s", messageStr.c_str());
        else
            ImGui::Text("%s", messageStr.c_str());
    }
    ImGui::EndChild();
    ImGui::End();
}
