#include "EntityFactory.h"


namespace graphics_engine::entities
{

    auto CreateEntityFactory(IEnginePtr spEngine) -> IEntityFactoryPtr
    {
        return std::make_shared<EntityFactory>(spEngine);
    }

    EntityFactory::EntityFactory(IEnginePtr spEngine)
		: m_spEngine(spEngine)
    {
    }

    auto EntityFactory::AddCube(const attributes::Attributes& attributes) -> Entity*
    {
        // Each face is made of two triangles with vertices determined by the following indices
        static const std::vector<unsigned int> indices = {
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

        return m_spEngine->GetEntityManager()->AddEntity(attributes, indices);
    }

}
