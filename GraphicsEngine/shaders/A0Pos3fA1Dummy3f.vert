// This shader takes two attributes of size 3f. The first attribute is used to
// fill gl_Position, while the second is simply passed along to the next 
// shader.

#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inAttr;

layout (location = 1) out vec3 outAttr;

void main()
{
	gl_Position = vec4(inPos, 1.0);

	// Just pass inAttr along to the next shader.
	outAttr = inAttr;
};
