// This shader takes two attributes, one of size 3f, and the other of size 2f. The first attribute is used to fill 
// gl_Position, while the second can be interpreted as texture coordinates.

#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inAttr;

out vec2 texCoord;

void main()
{
	gl_Position = vec4(inPos, 1.0);
	texCoord = inAttr;
};
