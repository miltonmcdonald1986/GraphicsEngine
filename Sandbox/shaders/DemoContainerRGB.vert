#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorVert;
layout (location = 2) in vec2 texCoordVert;

out vec3 colorFrag;
out vec2 texCoordFrag;

void main()
{
	gl_Position = vec4(pos, 1.0);
	colorFrag = colorVert;
	texCoordFrag = texCoordVert;
}
