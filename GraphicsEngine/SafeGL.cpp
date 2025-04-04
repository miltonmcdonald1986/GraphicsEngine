#include "pch.h"
#include "SafeGL.h"

#include "Error.h"

namespace GraphicsEngine::GL
{

	auto BindBuffer(GLenum target, GLuint buffer) -> void
	{
		glBindBuffer(target, buffer);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GetProgramiv(GLuint program, GLenum pname, GLint* params) -> void
	{
		glGetProgramiv(program, pname, params);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GetShaderiv(GLuint shader, GLenum pname, GLint* params) -> void
	{
		glGetShaderiv(shader, pname, params);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

}
