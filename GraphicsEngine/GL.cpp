#include "pch.h"
#include "GraphicsEngine/GL.h"

#include "glm/vec4.hpp"

#include "Error.h"
#include "SafeGL.h"
#include "GraphicsEngine/Uniform.h"

namespace GLHelpers
{

	/*const std::map<GraphicsEngine::GL::PolygonMode, GLenum> MapRasterizeModeToGLenum =
	{
		std::make_pair(GraphicsEngine::GL::PolygonMode::Point, GL_POINT),
		std::make_pair(GraphicsEngine::GL::PolygonMode::Line, GL_LINE),
		std::make_pair(GraphicsEngine::GL::PolygonMode::Fill, GL_FILL)
	};*/


	auto GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void
	{
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
		GraphicsEngine::HandleError(__FUNCTION__);
	}

	auto GetFloatv(GLenum pname, GLfloat* data) -> void
	{
		glGetFloatv(pname, data);
		GraphicsEngine::HandleError(__FUNCTION__);
	}
}

namespace GraphicsEngine::GL
{

	auto GetActiveUniform(GLuint programId, GLuint index) -> GEuniform
	{
		const GLsizei bufSize = 16; // maximum name length
		GLint size;
		GLenum type;
		std::string name(bufSize, '\0');
		GLsizei length; // name length
		GLHelpers::GetActiveUniform(programId, index, bufSize, &length, &size, &type, name.data());

		GEuniform uniform;
		switch (type)
		{
		case GL_FLOAT_VEC4:
		{
			GLint location = GL::GetUniformLocation(programId, name.data());

			float v[4];
			GL::GetUniformfv(programId, location, v);

			uniform.m_Type = GE_UNIFORM_TYPE_VEC4;
			uniform.m_Name = name.c_str();
			uniform.m_Location = location;
			std::copy(uniform.m_Data.vec4, uniform.m_Data.vec4 + 4, v);

			return uniform;
		}
		}

		// Apparently we're not handling a type that we need to be.
		DebugBreak();
		return GEuniform{ .m_Type = GE_UNIFORM_TYPE_EMPTY };
	}

	auto GetActiveUniforms(GLuint programId) -> std::vector<GEuniform>
	{
		std::vector<GEuniform> uniforms;
		auto count = GraphicsEngine::GL::GetNumActiveUniformVariables(programId);
		for (int i = 0; i < count; ++i)
		{
			uniforms.push_back(GraphicsEngine::GL::GetActiveUniform(programId, i));
		}

		return uniforms;
	}

	//auto GetPolygonMode() -> PolygonMode
	//{
	//	std::vector<GLint> param(2);
	//	GLHelpers::GetIntegerv(GL_POLYGON_MODE, param.data());

	//	switch (param[0])
	//	{
	//	case GL_POINT:
	//		return PolygonMode::Point;
	//	case GL_LINE:
	//		return PolygonMode::Line;
	//	default:
	//		return PolygonMode::Fill;
	//	}
	//}

	//auto SetPolygonMode(PolygonMode mode) -> void
	//{
	//	GLHelpers::PolygonMode(GL_FRONT_AND_BACK, GLHelpers::MapRasterizeModeToGLenum.at(mode));
	//}

	auto SetUniform(const GEuniform& uniform) -> void
	{
		switch (uniform.m_Type)
		{
		case GE_UNIFORM_TYPE_VEC4:
		{
			const float* v = uniform.m_Data.vec4;
			GL::Uniform4f(uniform.m_Location, v[0], v[1], v[2], v[3]);
			break;
		}
		}
	}

	auto GetCurrentProgram() -> GLuint
	{
		GLint prog = 0;
		GL::GetIntegerv(GL_CURRENT_PROGRAM, &prog);
		
		return prog;
	}

	auto GetNumActiveUniformVariables(GLuint programId) -> GLint
	{
		if (programId == 0)
			return 0;

		GLint count;
		GL::GetProgramiv(programId, GL_ACTIVE_UNIFORMS, &count);

		return count;
	}

}
