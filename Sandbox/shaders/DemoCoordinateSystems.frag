#version 330 core
out vec4 FragColor;

in vec2 oTextureCoordinates;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, oTextureCoordinates), texture(texture2, oTextureCoordinates), 0.2);
}
