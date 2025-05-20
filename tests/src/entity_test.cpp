// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// entity_test.h - Unit tests for the entity struct in the graphics engine.

#include <gtest/gtest.h>

#include "GraphicsEngine/IEngine.h"
#include "glfw/glfw3.h"

class GraphicsEngineTestFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    ASSERT_TRUE(glfwInit());

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    window_ = glfwCreateWindow(800, 600, "Hidden Window", nullptr, nullptr);
    ASSERT_TRUE(window_);

    glfwMakeContextCurrent(window_);
    ASSERT_EQ(glfwGetError(nullptr), GLFW_NO_ERROR);
  }

  void TearDown() override {
    glfwDestroyWindow(window_);
    glfwTerminate();
  }

 private:
  GLFWwindow* window_ = nullptr;
};

TEST_F(GraphicsEngineTestFixture, Entity) {
  graphics_engine::IEnginePtr engine = graphics_engine::CreateEngine();
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
