#include "Shader.h"

#include "Uniform.h"

namespace GraphicsEngine
{

	Shader::Shader (const std::tuple<Types::StringView, Types::OptStringView, Types::ShaderId, Types::StringViews, Types::StringView>& data)
		:	FRAGMENT_SHADER_SOURCE(std::get<0>(data)),
			GEOMETRY_SHADER_SOURCE(std::get<1>(data)),
			ID(std::get<2>(data)),
			UNIFORM_NAMES(std::get<3>(data)),
			VERTEX_SHADER_SOURCE(std::get<4>(data))
	{
	}

}
