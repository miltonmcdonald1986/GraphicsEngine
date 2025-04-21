#version 330 core

out vec4 fragColor;

in vec2 texCoordsFRAG;

uniform sampler2D uTextureContainer;
uniform sampler2D uTextureAwesomeFace;
uniform float uMix;

void main()
{
   fragColor = mix(texture(uTextureContainer, texCoordsFRAG), texture(uTextureAwesomeFace, texCoordsFRAG), uMix);
}
