#include "pch.h"
#include "Uniform.h"
#include "SafeGL.h"

#include "glm/gtc/type_ptr.hpp"

namespace GraphicsEngine
{

	auto CreateUniform(GLuint programId) -> UniformPtr
	{
		return UniformPtr(new Uniform(programId));
	}

	Uniform::Uniform(GLuint programId)
		: m_ProgramId(programId)
	{
	}

	auto GraphicsEngine::Uniform::GetData() const -> Data
	{
		return m_Data;
	}

	auto Uniform::GetLocation() const -> int
	{
		return m_Location;
	}

	auto Uniform::GetName() const -> std::string
	{
		return m_Name;
	}

	auto Uniform::SetData(const Data& data) -> void
	{
		m_Data = data;

		GL::UseProgram(m_ProgramId);
		if (std::holds_alternative<float>(data))
			GL::Uniform1f(m_Location, std::get<float>(data));
		else if (std::holds_alternative<glm::vec4>(data))
		{
			const float* v = glm::value_ptr(std::get<glm::vec4>(data));
			GL::Uniform4f(m_Location, v[0], v[1], v[2], v[3]);
		}
	}

	auto Uniform::SetLocation(GLint location) -> void
	{
		m_Location = location;
	}

	auto Uniform::SetName(const std::string& name) -> void
	{
		m_Name = name;
	}

}
