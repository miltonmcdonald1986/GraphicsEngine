#include "DemoTransformationsApp.h"

#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/vec4.hpp"

#include "GraphicsEngine/IAttribute.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IEntity.h"
#include "GraphicsEngine/ILog.h"
#include "GraphicsEngine/IShader.h"
#include "GraphicsEngine/IUniform.h"

DemoTransformationsApp::DemoTransformationsApp(GLFWwindow* pWindow)
    : App(pWindow)
{
    m_spEngine->SetBackgroundColor(GraphicsEngine::Color{ .r = 0.2f, .g = 0.3f, .b = 0.3f, .a = 1.f });
    
    GraphicsEngine::String sourceVert = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoordsFRAG;
  
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    texCoordsFRAG = vec2(aTexCoord.x, aTexCoord.y);
} )";

GraphicsEngine::String sourceFrag = R"(#version 330 core

out vec4 fragColor;

in vec2 texCoordsFRAG;

uniform sampler2D uTextureContainer;
uniform sampler2D uTextureAwesomeFace;
uniform float uMix;

void main()
{
   fragColor = mix(texture(uTextureContainer, texCoordsFRAG), texture(uTextureAwesomeFace, texCoordsFRAG), uMix);
})";

    std::vector<glm::vec3> vertices = {
        glm::vec3(-0.5f, -0.5f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f),
        glm::vec3(0.5f, 0.5f, 0.f),
        glm::vec3(-0.5f, 0.5f, 0.f)
    };

    std::vector<glm::vec2> texCoords = {
        glm::vec2(0.f, 0.f),
        glm::vec2(1.f, 0.f),
        glm::vec2(1.f, 1.f),
        glm::vec2(0.f, 1.f)
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    auto spEntity = m_spEngine->CreateNewEntity({
        GraphicsEngine::CreateAttribute(vertices),
        GraphicsEngine::CreateAttribute(texCoords)
    }, indices);

    m_spShader = m_spEngine->CreateNewShaderFromSource(sourceVert, "", sourceFrag);
    m_spShader->GetActiveUniform("uMix")->SetData(0.2f);

    spEntity->SetShader(m_spShader);

    auto spTextureContainer = m_spEngine->CreateNewTextureFromFile("uTextureContainer", "textures/container.jpg");
    auto spTextureAwesomeFace = m_spEngine->CreateNewTextureFromFile("uTextureAwesomeFace", "textures/awesomeface.png");
    spEntity->SetTextures({ spTextureContainer, spTextureAwesomeFace });
}

auto DemoTransformationsApp::Iterate() -> void
{
    static auto start = std::chrono::system_clock::now();
    auto now = std::chrono::system_clock::now();
    auto diff = now - start;
    auto seconds = std::chrono::duration<float>(diff).count();\

    auto trans = glm::mat4(1.f);
    trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));
    trans = glm::rotate(trans, seconds, glm::vec3(0.f, 0.f, 1.f));
    m_spShader->GetActiveUniform("transform")->SetData(trans);

    App::Iterate();
}
