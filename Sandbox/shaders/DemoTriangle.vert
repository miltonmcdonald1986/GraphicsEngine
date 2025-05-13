#version 330 core

layout (location = 0) in vec3 pos;

vec4 ApplyTransformationMatrix(vec3);	// GraphicsEngine::ShaderSnippets::Transformation

void main()
{
	gl_Position = ApplyTransformationMatrix(pos);
}
