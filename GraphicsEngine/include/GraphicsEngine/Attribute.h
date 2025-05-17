// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// Attribute.h - This file defines the attribute system used in the graphics
// engine, allowing flexible representation of vertex attributes.

#ifndef GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTE_H_
#define GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTE_H_

#include <expected>
#include <variant>
#include <vector>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include "Error.h"

namespace graphics_engine::attributes {

// Represents a vertex attribute, which can be a collection of 2D or 3D vectors.
using Attribute = std::variant<std::vector<glm::vec2>, std::vector<glm::vec3>>;

// A container for multiple attributes, useful for managing vertex data
// collectively.
using Attributes = std::vector<Attribute>;

// Represents an expected result for an attribute, allowing error handling when
// retrieving attributes.
using ExpectAttribute = std::expected<Attribute, Error>;

}  // namespace graphics_engine::attributes

#endif  // GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTE_H_
