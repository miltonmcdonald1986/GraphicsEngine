#include "DemoCoordinateSystemsUtilities.h"

#include "GraphicsEngine/IEngine.h"
#include "GraphicsEngine/IEntityFactory.h"

namespace Utilities
{

    auto CreateTenTexturedCubes(GraphicsEngine::IEnginePtr spEngine) -> GraphicsEngine::IEntities
    {
        auto [spShader, textures] = PrepareShaderAndTextures(spEngine);
        
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

        GraphicsEngine::IEntities cubes;
        for (size_t i = 0; i < positions.size(); ++i)
        {
            cubes.push_back(spEntityFactory->CreateCubeTextured(spShader, textures));
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            model = glm::rotate(model, glm::radians(20.f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            cubes.back()->SetModelMatrix(model);
        }

        return cubes;
    }

    auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::ShaderId, GraphicsEngine::ITextures>
    {
        auto result = std::make_pair(GraphicsEngine::ShaderId(0), GraphicsEngine::ITextures{});

        if (!spEngine)
            return result;

        auto shaderId = spEngine->GetShaderManager()->AddShaderFromFiles(std::filesystem::path(SHADERS_DIR)/"DemoCoordinateSystems.vert", std::filesystem::path(SHADERS_DIR)/"DemoCoordinateSystems.frag");
        if (shaderId == 0)
        {
            spEngine->GetLog()->Error("Failed to create shader.");
            return result;
        }

        GraphicsEngine::ITextures textures;

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

        result.first = shaderId;
        result.second = { spTexture1, spTexture2 };

        return result;
    }

}
