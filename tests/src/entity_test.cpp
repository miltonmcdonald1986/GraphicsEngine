// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// entity_test.h - Unit tests for the entity struct in the graphics engine.

#include <gtest/gtest.h>

#include "EGL/egl.h"
#include "GLFW/glfw3.h"
#include "GraphicsEngine/IEngine.h"

class GraphicsEngineTestFixture : public ::testing::Test {
 protected:
  void SetUp() override {
#ifdef _WIN32
    display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    ASSERT_TRUE(display_);
    ASSERT_EQ(eglInitialize(display_, nullptr, nullptr), EGL_TRUE);

    EGLConfig config = nullptr;
    EGLint num_configs;
    std::vector<EGLint> attribs = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,  // Request GLES 2.0
        EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,        // Offscreen rendering
        EGL_NONE};
    ASSERT_EQ(
        eglChooseConfig(display_, attribs.data(), &config, 1, &num_configs),
        EGL_TRUE);

    std::vector<EGLint> context_attribs = {EGL_CONTEXT_CLIENT_VERSION,
                                           2,  // Request OpenGL ES 2.0
                                           EGL_NONE};
    EGLContext context = eglCreateContext(display_, config, EGL_NO_CONTEXT,
                                          context_attribs.data());
    ASSERT_TRUE(context);
    ASSERT_TRUE(
        eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, context));

#else
    ASSERT_EQ(glfwInit(), GL_TRUE);

    // Create an invisible window for an OpenGL context
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window =
        glfwCreateWindow(640, 480, "Hidden Context", nullptr, nullptr);
    ASSERT_TRUE(window);

    // Make the context current
    glfwMakeContextCurrent(window);
#endif
  }

  void TearDown() override {
#ifdef _WIN32
    eglDestroyContext(display_, context_);
    eglTerminate(display_);
#else
    glfwDestroyWindow(window);
    glfwTerminate();
#endif
  }

 private:
  EGLContext context_;
  EGLDisplay display_;
};

TEST_F(GraphicsEngineTestFixture, Entity) {
  graphics_engine::IEnginePtr engine = graphics_engine::CreateEngine(
      graphics_engine::GLProcAddressFunc(eglGetProcAddress));
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
