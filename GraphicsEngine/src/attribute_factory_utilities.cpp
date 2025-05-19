// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// attribute_factory_utilities.h - Utility functions for use by abstract_factory
// functions.

#include "attribute_factory_utilities.h"

namespace graphics_engine::attributes::attribute_factory::utilities {

namespace {

const std::string kErrMessageEmptyVector =
    "Empty vector was provided to a function that requires a non-empty vector.";

}

void center_triangle(glm::vec3& v0, glm::vec3& v1,
                                           glm::vec3& v2) {
  std::expected<glm::vec3, Error> centroid = compute_centroid({v0, v1, v2});
  assert(centroid.has_value());
  for (auto v : {&v0, &v1, &v2}) {
    *v -= *centroid;
  }
}

std::expected<glm::vec3, Error> compute_centroid(
    const std::vector<glm::vec3>& vertices) {
  if (vertices.empty())
    return std::unexpected(
        Error{ErrorCode::kInvalidInput, kErrMessageEmptyVector});

  return std::accumulate(vertices.begin(), vertices.end(),
                         glm::vec3(0.f, 0.f, 0.f)) /
         static_cast<float>(vertices.size());
}

bool satisfies_triangle_inequality(float side_a, float side_b, float side_c) {
  return (side_a + side_b > side_c) && (side_a + side_c > side_b) &&
         (side_b + side_c > side_a);
}

}  // namespace graphics_engine::attributes::attribute_factory::utilities
