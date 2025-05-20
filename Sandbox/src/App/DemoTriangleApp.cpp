#include "DemoTriangleApp.h"

#include <numbers>

#include "GraphicsEngine/attribute_factory.h"
#include "GraphicsEngine/ICameraViewport.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/ShaderSnippets.h"
#include "GraphicsEngine/ShaderUtilities.h"
#include "glm/gtc/matrix_access.hpp"

namespace g = ::graphics_engine;

auto OnCamera(g::IEnginePtr spEngine, const glm::mat4& /*view*/,
              const glm::mat4& projection) -> void {
  if (!spEngine) return;

  spEngine->GetShaderManager()->GetCurrentShader()->SetUniformData(
      "transformationMatrix", projection);
}

DemoTriangleApp::DemoTriangleApp(GLFWwindow* pWindow) : App(pWindow) {
  if (!pWindow) return;

  // Get the engine
  auto spEngine = GetEngine();

  // Set some misc items
  spEngine->SetBackgroundColor(
      g::Types::Color{.r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f});
  spEngine->SetPolygonMode(g::Types::PolygonMode::Fill);

  // Create a triangle
  auto attr = g::attributes::attribute_factory::triangle::SSS(1.f, 1.f, 1.f);
  assert(attr.has_value());
  auto pEntity = spEngine->GetEntityManager()->AddEntity({attr.value()});

  // Create a shader
  auto shadersDir = g::Types::Path(SHADERS_DIR);
  std::string vertexShader =
      g::ShaderUtilities::GetSourceFromFile(shadersDir / "DemoTriangle.vert") +
      g::ShaderSnippets::Transformation;
  std::string fragmentShader =
      g::ShaderUtilities::GetSourceFromFile(shadersDir / "DemoTriangle.frag");
  pEntity->shader = spEngine->GetShaderManager()->AddShaderFromSource(
      vertexShader, fragmentShader);

  // Create a camera
  spEngine->SetCamera(g::CreateCameraViewport());
  spEngine->GetCamera()->GetObservable()->AddObserver(
      [this](const glm::mat4& view, const glm::mat4& projection) {
        OnCamera(GetEngine(), view, projection);
      });

  int width;
  int height;
  glfwGetFramebufferSize(pWindow, &width, &height);
  AppCallbacks::OnFramebufferSize(pWindow, width, height);
}
