#pragma once

#include "Types.h"

namespace graphics_engine
{

	struct Uniform
	{
		Uniform() = delete;
		Uniform(Types::StringView name, int location);
		Uniform (const Uniform& other);

		const Types::String name;
		const int location;
		Types::UniformData data;
	};

	using Uniforms = std::unordered_map<Types::String, Uniform, Types::StringHash, std::equal_to<>>;

}
