#pragma once

struct GLFWwindow;

auto InitializeGLFW() -> GLFWwindow*;
auto OnFramebufferSize(GLFWwindow* window, int width, int height) -> void;
auto TerminateGLFW(GLFWwindow* pWindow) -> void;
