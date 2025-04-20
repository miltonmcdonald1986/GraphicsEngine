#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colorVert;

out vec3 colorFrag;

void main()
{
	gl_Position = vec4(pos, 1.0);

	// Just pass inAttr along to the next shader.
	colorFrag = colorVert;
};
