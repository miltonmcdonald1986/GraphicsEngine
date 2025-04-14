#version 330 core

out vec4 FragColor;

uniform float uGreenScalar;

void main()
{
   FragColor = vec4(0., 1.f*uGreenScalar, 0.f, 1.0f);
}
