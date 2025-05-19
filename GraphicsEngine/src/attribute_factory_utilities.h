// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// attribute_factory_utilities.h - Utility functions for use by abstract_factory
// functions.

#ifndef GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTEFACTORYUTILITIES_H_
#define GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTEFACTORYUTILITIES_H_

#include <expected>
#include <vector>

#include "glm/vec3.hpp"

#include "Error.h"

namespace graphics_engine::attributes::attribute_factory::utilities {

std::expected<void, Error> center_triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2);
std::expected<glm::vec3, Error> compute_centroid(
    const std::vector<glm::vec3>& vertices);
bool is_valid_triangle(float side_a, float side_b, float side_c);

}  // namespace graphics_engine::attributes::attribute_factory::utilities

#endif  // GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTEFACTORYUTILITIES_H_
