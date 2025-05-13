#include "Shader.h"

#include "Uniform.h"

namespace GraphicsEngine
{

	namespace
	{

		auto GetKeys (const Uniforms& uniforms)
		{
			Types::StringViews keys;
			std::transform (uniforms.begin (), uniforms.end (), std::back_inserter (keys), [] (const std::pair<Types::StringView, Uniform>& uniform)
				{
					return uniform.first;
				});

			return keys;
		}

	}

	Shader::Shader (const std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Uniforms, Types::StringView>& data)
		:	FRAGMENT_SHADER_SOURCE(std::get<0>(data)),
			GEOMETRY_SHADER_SOURCE(std::get<1>(data)),
			ID(std::get<2>(data)),
			UNIFORM_NAMES(GetKeys(std::get<3>(data))),
			VERTEX_SHADER_SOURCE(std::get<4>(data))
	{
	}

}
