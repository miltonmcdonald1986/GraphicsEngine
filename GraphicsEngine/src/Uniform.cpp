#include "pch.h"
#include "Uniform.h"

namespace GraphicsEngine
{

	auto CreateUniform() -> UniformPtr
	{
		return UniformPtr(new Uniform());
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
