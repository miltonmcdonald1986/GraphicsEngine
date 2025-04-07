#pragma once

struct GLFWwindow;

auto InitializeDearImGui(GLFWwindow* pWindow) -> bool;
auto TerminateDearImGui() -> void;
