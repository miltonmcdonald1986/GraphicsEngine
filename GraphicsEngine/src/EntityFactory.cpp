#include "EntityFactory.h"

#include "IAttribute.h"

namespace GraphicsEngine
{

    auto CreateEntityFactory(IEnginePtr spEngine) -> IEntityFactoryPtr
    {
        return std::make_shared<EntityFactory>(spEngine);
    }

    EntityFactory::EntityFactory(IEnginePtr spEngine)
		: m_spEngine(spEngine)
    {
    }

    auto EntityFactory::CreateCubeTextured(IShaderPtr spShader, ITextures textures) -> IEntityPtr
	{
        GraphicsEngine::IAttributePtr spAttrVertices = GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{
            glm::vec3(-0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, 0.5f, -0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, 0.5f, -0.5f),
            glm::vec3(0.5f, 0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, 0.5f),
            glm::vec3(-0.5f, -0.5f, 0.5f),
            glm::vec3(-0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(0.5f, 0.5f, -0.5f),
            glm::vec3(-0.5f, 0.5f, -0.5f)
        });

        GraphicsEngine::IAttributePtr spAttrTexCoords = GraphicsEngine::CreateAttribute(std::vector<glm::vec2>{
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f),
            glm::vec2(0.f, 0.f),
            glm::vec2(1.f, 0.f),
            glm::vec2(1.f, 1.f),
            glm::vec2(0.f, 1.f)
        });

        std::vector<unsigned int> indices = {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            8, 9, 10,
            10, 11, 8,
            12, 13, 14,
            14, 15, 12,
            16, 17, 18,
            18, 19, 16,
            20, 21, 22,
            22, 23, 20
        };

        auto spEntity = m_spEngine->CreateNewEntity({ spAttrVertices, spAttrTexCoords }, indices);
        if (!m_spEngine)
        {
            m_spEngine->GetLog()->Error("Failed to create entity.");
            return nullptr;
        }

        spEntity->SetShader(spShader);
        spEntity->SetTextures(textures);

        return spEntity;
	}

}
