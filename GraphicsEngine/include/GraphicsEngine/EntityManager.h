#pragma once

#include "Types.h"
#include "entity.h"

namespace graphics_engine::entities {

/// @class EntityManager
/// @brief Abstract base class for managing the lifecycle and retrieval of
/// entities within the graphics engine.
///
/// This class defines the interface for entity management and ensures that it
/// cannot be instantiated or copied/moved outside the Engine.
class EntityManager {  // NOLINT(cppcoreguidelines-virtual-class-destructor)
 public:
  /// @brief Deleted copy constructor to prevent copying.
  EntityManager(const EntityManager&) = delete;

  /// @brief Deleted copy assignment operator to prevent assignment.
  auto operator=(const EntityManager&) -> EntityManager& = delete;

  /// @brief Deleted move constructor to prevent moving.
  EntityManager(EntityManager&&) = delete;

  /// @brief Deleted move assignment operator to prevent move assignment.
  auto operator=(EntityManager&&) -> EntityManager& = delete;

  /// @brief Adds a new entity to the manager.
  /// @param attributes Vertex attributes defining the entity's geometry.
  /// @param indices Optional index buffer specifying the order in which
  /// vertices are drawn.
  /// @return Pointer to the newly created Entity.
  virtual auto AddEntity(const attributes::Attributes& attributes,
                         const Types::Indices& indices = {}) -> Entity* = 0;

  /// @brief Retrieves an entity by its unique ID.
  /// @param id The identifier of the entity.
  /// @return Pointer to the requested Entity, or `nullptr` if not found.
  virtual auto GetEntity(Types::EntityId id) -> Entity* = 0;

  /// @brief Gets a collection of all registered entity IDs.
  /// @return A list of entity IDs currently managed by the EntityManager.
  [[nodiscard]] virtual auto GetEntityIds() const -> Types::EntityIds = 0;

 protected:
  /// @brief Protected to prevent direct instantiation.
  ///
  /// Only derived classes created by Engine can be instantiated.
  EntityManager() = default;

  /// @brief Virtual destructor for proper cleanup of derived classes.
  virtual ~EntityManager() = default;
};

}  // namespace graphics_engine::entities
