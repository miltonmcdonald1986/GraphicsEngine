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

    auto EntityFactory::CreateCubeTextured(Id shaderId, const ITextures& textures) -> Entity*
	{
        // A cube has eight vertices
        auto v0 = glm::vec3(-0.5f, -0.5f,  0.5f);
        auto v1 = glm::vec3( 0.5f, -0.5f,  0.5f);
        auto v2 = glm::vec3( 0.5f,  0.5f,  0.5f);
        auto v3 = glm::vec3(-0.5f,  0.5f,  0.5f);
        auto v4 = glm::vec3( 0.5f, -0.5f, -0.5f);
        auto v5 = glm::vec3( 0.5f,  0.5f, -0.5f);
        auto v6 = glm::vec3(-0.5f, -0.5f, -0.5f);
        auto v7 = glm::vec3(-0.5f,  0.5f, -0.5f);

        // A cube has six faces
        GraphicsEngine::IAttributePtr spAttrVertices = GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{
            v0, v1, v2, v3, // FACE 0
            v1, v4, v5, v2, // FACE 1
            v4, v6, v7, v5, // FACE 2
            v6, v0, v3, v7, // FACE 3
            v6, v4, v1, v0, // FACE 4
            v3, v2, v5, v7  // FACE 5
            });

        // Each face has four texture coordinates, which we apply in counterclockwise order.
        auto t0 = glm::vec2(0.f, 0.f);
		auto t1 = glm::vec2(1.f, 0.f);
		auto t2 = glm::vec2(1.f, 1.f);
		auto t3 = glm::vec2(0.f, 1.f);
        
        // Associate each face to the texture coordinates
        GraphicsEngine::IAttributePtr spAttrTexCoords = GraphicsEngine::CreateAttribute(std::vector<glm::vec2>{
			t0, t1, t2, t3, // FACE 0
			t0, t1, t2, t3, // FACE 1
			t0, t1, t2, t3, // FACE 2
			t0, t1, t2, t3, // FACE 3
			t0, t1, t2, t3, // FACE 4
			t0, t1, t2, t3  // FACE 5
        });

        // Each face is made of two triangles with vertices determined by the following indices
        std::vector<unsigned int> indices = {
            0, 1, 2,    // FACE 0, triangle 0
			2, 3, 0,    // FACE 0, triangle 1
			4, 5, 6,    // FACE 1, triangle 0
			6, 7, 4,    // FACE 1, triangle 1
			8, 9, 10,   // FACE 2, triangle 0
			10, 11, 8,  // FACE 2, triangle 1
			12, 13, 14, // FACE 3, triangle 0
			14, 15, 12, // FACE 3, triangle 1
			16, 17, 18, // FACE 4, triangle 0
			18, 19, 16, // FACE 4, triangle 1
			20, 21, 22, // FACE 5, triangle 0
			22, 23, 20  // FACE 5, triangle 1
        };

        auto pEntity = m_spEngine->GetEntityManager()->AddEntity({ spAttrVertices, spAttrTexCoords }, indices);
        
        pEntity->shaderId = shaderId;
        pEntity->textures = textures;

        return pEntity;
	}

}
