// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// entity_test.h - Unit tests for the entity struct in the graphics engine.

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

#include <gtest/gtest.h>

#include <cstdlib>

#include "GLFW/glfw3.h"
#include "GraphicsEngine/IEngine.h"

class GraphicsEngineTestFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    const char* github_actions = std::getenv("GITHUB_ACTIONS");
    bool is_ci = github_actions && (std::string(github_actions) == "true");

    if (is_ci)
      glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_NULL);

    ASSERT_EQ(glfwInit(), GL_TRUE);

    if (is_ci)
      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_OSMESA_CONTEXT_API);

    window_ = glfwCreateWindow(800, 600, "Headless", nullptr, nullptr);
    ASSERT_TRUE(window_);

    glfwMakeContextCurrent(window_);
  }

  void TearDown() override {
    glfwDestroyWindow(window_);
    glfwTerminate();
  }

 private:
  GLFWwindow* window_;
};

TEST_F(GraphicsEngineTestFixture, Entity) {
  graphics_engine::IEnginePtr engine = graphics_engine::CreateEngine(
      std::optional<graphics_engine::GLProcAddressFunc>{
          reinterpret_cast<graphics_engine::GLProcAddressFunc>(
              glfwGetProcAddress)});
  EXPECT_TRUE(engine);

  graphics_engine::entities::Entity* entity =
      engine->GetEntityManager()->AddEntity({});
  EXPECT_FALSE(entity->cameraCallback);
  EXPECT_EQ(entity->kEntityId, 1);
  EXPECT_EQ(entity->kNumIndices, 0);
  EXPECT_EQ(entity->kNumVertices, 0);
  EXPECT_EQ(entity->modelMatrix, glm::mat4(1.f));
  EXPECT_EQ(entity->shader, nullptr);
  EXPECT_EQ(entity->textures, graphics_engine::ITextures{});
}
