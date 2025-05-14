#include "DemoCoordinateSystemsUtilities.h"

#include "GraphicsEngine/AttributeFactory.h"
#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IEntityFactory.h"

namespace Utilities
{

    auto CreateTenTexturedCubes(GraphicsEngine::IEnginePtr spEngine) -> std::vector<GraphicsEngine::Entity*>
    {
        auto [pShader, textures] = PrepareShaderAndTextures(spEngine);
        
        auto spEntityFactory = GraphicsEngine::CreateEntityFactory(spEngine);

        std::vector<glm::vec3> positions = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
        };

        std::vector<GraphicsEngine::Entity*> cubes;
        for (size_t i = 0; i < positions.size(); ++i)
        {
            auto attrPos = GraphicsEngine::AttributeFactory::Cube::Position();
            auto attrTexCoords = GraphicsEngine::AttributeFactory::Cube::TextureCoordinates();
            auto spCube = spEntityFactory->AddCube({ attrPos, attrTexCoords });
            spCube->pShader = pShader;
            spCube->textures = textures;

            cubes.push_back(spCube);
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            model = glm::rotate(model, glm::radians(20.f * static_cast<float>(i)), glm::vec3(1.0f, 0.3f, 0.5f));
            cubes.back()->modelMatrix = model;
        }

        return cubes;
    }

    auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::Shader*, GraphicsEngine::ITextures>
    {
        GraphicsEngine::Shader* pShader = nullptr;
        auto result = std::make_pair(pShader, GraphicsEngine::ITextures{});

        if (!spEngine)
            return result;

        pShader = spEngine->GetShaderManager()->AddShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoCoordinateSystems.vert", std::filesystem::path(SHADERS_DIR)/"DemoCoordinateSystems.frag");
        if (!pShader)
        {
            spEngine->GetLog()->Error("Failed to create shader.");
            return result;
        }

        auto spTexture1 = spEngine->CreateNewTextureFromFile("texture1", std::filesystem::path(TEXTURES_DIR)/"container.jpg");
        if (!spTexture1)
        {
            spEngine->GetLog()->Error("Failed to load texture.");
            return result;
        }

        auto spTexture2 = spEngine->CreateNewTextureFromFile("texture2", std::filesystem::path(TEXTURES_DIR)/"awesomeface.png");
        if (!spTexture2)
        {
            spEngine->GetLog()->Error("Failed to load texture.");
            return result;
        }

        result.first = pShader;
        result.second = { spTexture1, spTexture2 };

        return result;
    }

}
