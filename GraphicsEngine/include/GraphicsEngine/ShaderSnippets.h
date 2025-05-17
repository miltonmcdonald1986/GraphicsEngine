#pragma once

#include <string>

namespace graphics_engine::ShaderSnippets
{

inline const std::string Transformation = R"(

uniform mat4 model;
uniform mat4 transformationMatrix;
uniform mat4 view;
uniform mat4 projection;
	
vec4 ApplyMVP(vec3 pos)
{
	return projection*view*model*vec4(pos, 1.);
}

vec4 ApplyTransformationMatrix(vec3 pos)
{
	return transformationMatrix*vec4(pos, 1.);
}

)";

}
