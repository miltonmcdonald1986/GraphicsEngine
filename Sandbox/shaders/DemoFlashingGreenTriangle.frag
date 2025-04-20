#version 330 core

out vec4 FragColor;

uniform float uGreenScalar;

void main()
{
   FragColor = vec4(0., 1.*uGreenScalar, 0., 1.);
}
