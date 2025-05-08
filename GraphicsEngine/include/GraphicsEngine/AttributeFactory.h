#pragma once

#include "IAttribute.h"
#include "DllImpExp.h"

namespace GraphicsEngine::AttributeFactory::Triangle
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
	/// @return A pointer to the created position attribute representing the triangle.
	GRAPHICSENGINE_API auto AAS(float A, float B, float a) -> GraphicsEngine::IAttributePtr;

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
	GRAPHICSENGINE_API auto ASA(float A, float c, float B) -> GraphicsEngine::IAttributePtr;

	/// @brief Creates a vertex attribute with three vertices based on the 
	/// Hypotenuse-Leg (HL) triangle configuration.
	/// 
	/// This function generates a position attribute for a right triangle using 
	/// the lengths of the hypotenuse and a leg.
	///
	/// @param hypotenuse The length of the hypotenuse.
	/// @param leg The length of a leg.
	/// @return A pointer to the created position attribute representing the triangle.
	GRAPHICSENGINE_API auto HL(float hypotenuse, float leg) -> GraphicsEngine::IAttributePtr;

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
	GRAPHICSENGINE_API auto SAS(float a, float C, float b) -> GraphicsEngine::IAttributePtr;

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
	GRAPHICSENGINE_API auto SSS(float a, float b, float c) -> GraphicsEngine::IAttributePtr;

}
