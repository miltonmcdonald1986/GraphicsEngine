// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// AttributeFactory.h - Defines utility functions for creating vertex
// attributes.

#ifndef GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTEFACTORY_H_
#define GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTEFACTORY_H_

#include "attribute.h"
#include "DllImpExp.h"

namespace graphics_engine::attributes::attribute_factory {

namespace cube {

/// @brief Creates a vertex attribute representing the positions of the cube's
/// vertices.
///
/// This function generates a position attribute for a cube, defining the 3D
/// coordinates of its vertices in space. The attribute contains 24 vertices
/// for a unit cube centered at the origin, ensuring each face of the cube has
/// unique vertices for proper rendering.
///
/// @return A pointer to the created position attribute.
DLLEXPORT Attribute Position();

/// @brief Creates a vertex attribute representing texture coordinates for a
/// cube.
///
/// This function generates a texture coordinate attribute for a cube, which
/// can be used to map textures onto the cube's surface. The attribute contains
/// 24 vertices, with each face of the cube having texture coordinates that
/// range from 0 to 1, ensuring proper texture mapping for all six faces.
///
/// @return A pointer to the created texture coordinate attribute.
DLLEXPORT Attribute TextureCoordinates();

}  // namespace cube

namespace triangle {

/// @brief Creates a vertex attribute with three vertices based on the
/// Angle-Angle-Side (AAS) triangle configuration.
///
/// This function generates a position attribute for a triangle using
/// two angles and a non-included side.
///
/// @param angle_a The first angle (in radians).
/// @param angle_b The second angle (in radians).
/// @param side_a The length of the side opposite angle @p A.
/// @return A `std::expected` containing the created position attribute if
/// successful, or an `Error` if the input is invalid.
DLLEXPORT std::expected<Attribute, Error> AAS(float angle_a, float angle_b,
                                              float side_a);

/// @brief Creates a vertex attribute with three vertices based on the
/// Angle-Side-Angle (ASA) triangle configuration.
///
/// This function generates a position attribute for a triangle using
/// two angles and the length of the side between them.
///
/// @param angle_a The first angle (in radians).
/// @param side_c The length of the included side.
/// @param angle_b The second angle (in radians).
/// @return A pointer to the created position attribute representing the
/// triangle.
DLLEXPORT std::expected<Attribute, Error> ASA(float angle_a, float side_c,
                                              float angle_b);

/// @brief Creates a vertex attribute with three vertices based on the
/// Hypotenuse-Leg (HL) triangle configuration.
///
/// This function generates a position attribute for a right triangle using
/// the lengths of the hypotenuse and a leg.
///
/// @param hypotenuse The length of the hypotenuse.
/// @param leg The length of a leg.
/// @return A pointer to the created position attribute representing the
/// triangle.
DLLEXPORT std::expected<Attribute, Error> HL(float hypotenuse, float leg);

/// @brief Creates a vertex attribute with three vertices based on the
/// Side-Angle-Side (SAS) triangle configuration.
///
/// This function generates a position attribute for a triangle using
/// the lengths of two sides and the angle between them.
///
/// @param side_a The length of the first side of the triangle.
/// @param angle_c The angle (in radians) between the two sides.
/// @param side_b The length of the second side of the triangle.
/// @return A pointer to the created position attribute representing the
/// triangle.
DLLEXPORT std::expected<Attribute, Error> SAS(float side_a, float angle_c, float side_b);

/// @brief Creates a vertex attribute with three vertices based on the
/// Side-Side-Side (SSS) triangle configuration.
///
/// This function generates a position attribute for a triangle using
/// the lengths of all three sides.
///
/// @param a The length of the first side of the triangle.
/// @param b The length of the second side of the triangle.
/// @param c The length of the third side of the triangle.
/// @return A pointer to the created position attribute representing the
/// triangle.
DLLEXPORT std::expected<Attribute, Error> SSS(float a, float b, float c);

}  // namespace triangle

}  // namespace graphics_engine::attributes::attribute_factory

#endif  // GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_ATTRIBUTEFACTORY_H_
