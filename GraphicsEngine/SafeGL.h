#pragma once

#include "glad/glad.h"

namespace GraphicsEngine::GL
{

	auto BindBuffer(GLenum target, GLuint buffer) -> void;
	auto GetProgramiv(GLuint program, GLenum pname, GLint* params) -> void;
	auto GetShaderiv(GLuint shader, GLenum pname, GLint* params) -> void;

}
