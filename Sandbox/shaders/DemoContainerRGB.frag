#version 330 core

out vec4 fragColor;

in vec3 colorFrag;
in vec2 texCoordFrag;

uniform sampler2D uTexture;

void main()
{
   fragColor = texture(uTexture, texCoordFrag)*vec4(colorFrag, 1.);
}
