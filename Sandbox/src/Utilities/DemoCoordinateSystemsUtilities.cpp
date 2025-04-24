#include "DemoCoordinateSystemsUtilities.h"

#include "GraphicsEngine/IEngine.h"

namespace Utilities
{

    auto PrepareShaderAndTextures(GraphicsEngine::IEnginePtr spEngine) -> std::pair<GraphicsEngine::IShaderPtr, GraphicsEngine::ITextures>
    {
        auto result = std::make_pair(GraphicsEngine::IShaderPtr(nullptr), GraphicsEngine::ITextures{});

        if (!spEngine)
            return result;

        auto spShader = spEngine->CreateNewShaderFromFiles("shaders/DemoCoordinateSystems.vert", "", "shaders/DemoCoordinateSystems.frag");
        if (!spShader)
        {
            spEngine->GetLog()->Error("Failed to create shader.");
            return result;
        }

        GraphicsEngine::ITextures textures;

        auto spTexture1 = spEngine->CreateNewTextureFromFile("texture1", "textures/container.jpg");
        if (!spTexture1)
        {
            spEngine->GetLog()->Error("Failed to load texture.");
            return result;
        }

        auto spTexture2 = spEngine->CreateNewTextureFromFile("texture2", "textures/awesomeface.png");
        if (!spTexture2)
        {
            spEngine->GetLog()->Error("Failed to load texture.");
            return result;
        }

        result.first = spShader;
        result.second = { spTexture1, spTexture2 };

        return result;
    }

}
