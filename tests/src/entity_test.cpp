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

namespace g = graphics_engine;
namespace ge = g::entities;

namespace {

bool IsCi() {
  const char* env = std::getenv("GITHUB_ACTIONS");
  return env && (std::string(env) == "true");
}

g::GLLoadProc GetProcAddress() {
  return reinterpret_cast<g::GLLoadProc>(glfwGetProcAddress);  // NOSONAR
}

}  // namespace

class GraphicsEngineTestFixture : public ::testing::Test {
 protected:
  void SetUp() override {
    
    if (IsCi()) {
      glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_NULL);
    }

    ASSERT_EQ(glfwInit(), GL_TRUE);

    if (IsCi()) {
      glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_OSMESA_CONTEXT_API);
    } else {
      glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    }

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
  g::IEnginePtr engine = g::CreateEngine(GetProcAddress());
  EXPECT_TRUE(engine);

  ge::Entity* entity = engine->GetEntityManager()->AddEntity({});
  EXPECT_FALSE(entity->cameraCallback);
  EXPECT_EQ(entity->kEntityId, 1);
  EXPECT_EQ(entity->kNumIndices, 0);
  EXPECT_EQ(entity->kNumVertices, 0);
  EXPECT_EQ(entity->modelMatrix, glm::mat4(1.f));
  EXPECT_EQ(entity->shader, nullptr);
  EXPECT_EQ(entity->textures, g::ITextures{});
}
