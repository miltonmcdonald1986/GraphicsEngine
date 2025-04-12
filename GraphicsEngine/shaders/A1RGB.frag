// For this shader, the output color is the attribute in location 1. Thus each
// vertex will have its own individual color, which can lead to a rainbow type
// effect, or be used for gradient color, etc.

#version 420 core

layout (location = 1) in vec3 inRGB;

out vec4 FragColor;

void main()
{
	FragColor = vec4(inRGB.r, inRGB.g, inRGB.b, 1.);
};
