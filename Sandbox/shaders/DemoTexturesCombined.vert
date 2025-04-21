#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoordsVERT;

out vec2 texCoordsFRAG;

void main()
{
	gl_Position = vec4(pos, 1.0);
	texCoordsFRAG = texCoordsVERT;
}
