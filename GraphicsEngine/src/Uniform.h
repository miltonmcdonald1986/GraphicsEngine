/// @file Uniform.h
/// @brief Defines the Uniform structure for managing shader uniforms.
/// 
/// This file contains the definition of the `Uniform` struct, including
/// attributes for name, location, and data storage. It is part of the 
/// graphics engine's shader management system.
/// 
/// @author Milton T. McDonald
/// @date 2025-05-02

#pragma once

#include "Types.h"

namespace GraphicsEngine
{

	/// @brief Represents a shader uniform.
	struct Uniform
	{
		/// @brief Deleted constructor to prevent instantiation.
		Uniform() = delete;

		/// @brief Constructs a Uniform object with a given name and location.
		/// @param name The name of the uniform.
		/// @param location The location of the uniform in the shader program.
		Uniform(StringView name, int location);

		/// @brief The name of the uniform.
		const String Name;

		/// @brief The location of the uniform in the shader program.
		const int Location;

		/// @brief Stores the data associated with this uniform.
		UniformData Data;
	};

}
