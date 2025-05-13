#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 projection;

vec4 ApplyProjection(vec3 position)
{
	return projection*vec4(position, 1.);
}

void main()
{
   gl_Position = ApplyProjection(pos);
}
