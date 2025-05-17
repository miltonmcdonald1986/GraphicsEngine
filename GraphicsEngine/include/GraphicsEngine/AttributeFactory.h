// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.

#pragma once

#include <expected>

#include "Error.h"
#include "Types.h"
#include "DllImpExp.h"

namespace GraphicsEngine::AttributeFactory 
{

	namespace Cube
	{

		/// @brief Creates a vertex attribute representing the positions of the cube's vertices.
		/// 
		/// This function generates a position attribute for a cube, defining the 3D coordinates 
		/// of its vertices in space. The attribute contains 24 vertices for a unit cube centered 
		/// at the origin, ensuring each face of the cube has unique vertices for proper rendering.
		///
		/// @return A pointer to the created position attribute.
		GRAPHICSENGINE_API auto Position () -> Types::VertexAttribute;

		/// @brief Creates a vertex attribute representing texture coordinates for a cube.
		/// 
		/// This function generates a texture coordinate attribute for a cube, which can be 
		/// used to map textures onto the cube's surface. The attribute contains 24 vertices, 
		/// with each face of the cube having texture coordinates that range from 0 to 1, 
		/// ensuring proper texture mapping for all six faces.
		///
		/// @return A pointer to the created texture coordinate attribute.
		GRAPHICSENGINE_API auto TextureCoordinates() -> Types::VertexAttribute;

	}

	namespace Triangle
	{

		/// @brief Creates a vertex attribute with three vertices based on the 
		/// Angle-Angle-Side (AAS) triangle configuration.
		/// 
		/// This function generates a position attribute for a triangle using 
		/// two angles and a non-included side.
		///
		/// @param A The first angle (in radians).
		/// @param B The second angle (in radians).
		/// @param a The length of the side opposite angle @p A.
		/// @return A `std::expected` containing the created position attribute if successful, 
		///         or an `Error` if the input is invalid.
		GRAPHICSENGINE_API auto AAS(float A, float B, float a) -> std::expected<Types::VertexAttribute, Error>;

		/// @brief Creates a vertex attribute with three vertices based on the 
		/// Angle-Side-Angle (ASA) triangle configuration.
		/// 
		/// This function generates a position attribute for a triangle using 
		/// two angles and the length of the side between them.
		///
		/// @param A The first angle (in radians).
		/// @param c The length of the included side.
		/// @param B The second angle (in radians).
		/// @return A pointer to the created position attribute representing the triangle.
		GRAPHICSENGINE_API auto ASA(float A, float c, float B) -> Types::VertexAttribute;

		/// @brief Creates a vertex attribute with three vertices based on the 
		/// Hypotenuse-Leg (HL) triangle configuration.
		/// 
		/// This function generates a position attribute for a right triangle using 
		/// the lengths of the hypotenuse and a leg.
		///
		/// @param hypotenuse The length of the hypotenuse.
		/// @param leg The length of a leg.
		/// @return A pointer to the created position attribute representing the triangle.
		GRAPHICSENGINE_API auto HL(float hypotenuse, float leg) -> Types::VertexAttribute;

		/// @brief Creates a vertex attribute with three vertices based on the 
		/// Side-Angle-Side (SAS) triangle configuration.
		/// 
		/// This function generates a position attribute for a triangle using 
		/// the lengths of two sides and the angle between them.
		///
		/// @param a The length of the first side of the triangle.
		/// @param C The angle (in radians) between the two sides.
		/// @param b The length of the second side of the triangle.
		/// @return A pointer to the created position attribute representing the triangle.
		GRAPHICSENGINE_API auto SAS(float a, float C, float b) -> Types::VertexAttribute;

		/// @brief Creates a vertex attribute with three vertices based on the 
		/// Side-Side-Side (SSS) triangle configuration.
		/// 
		/// This function generates a position attribute for a triangle using 
		/// the lengths of all three sides.
		///
		/// @param a The length of the first side of the triangle.
		/// @param b The length of the second side of the triangle.
		/// @param c The length of the third side of the triangle.
		/// @return A pointer to the created position attribute representing the triangle.
		GRAPHICSENGINE_API auto SSS(float a, float b, float c) -> Types::VertexAttribute;

	}

}