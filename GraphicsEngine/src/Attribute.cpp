#include "pch.h"
#include "Attribute.h"
#include "Log.h"

#include "glm/gtc/type_ptr.hpp"

namespace GraphicsEngine
{

	auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr
	{
		return std::make_shared<Attribute>(data);
	}

	Attribute::Attribute(const std::vector<glm::vec3>& data)
	{
		m_NumBytes = 3 * sizeof(float) * data.size();
		m_Data = glm::value_ptr(*data.data());
		m_NumComponents = 3;
		m_NumVertices = static_cast<GLuint>(data.size());
		m_Stride = 3 * sizeof(float);
		m_Type = GL_FLOAT;

		LOG_DEBUG(std::format("Created new attribute:\n"
			"NumBytes: {}\n"
			"Data: {}\n"
			"NumComponents: {}\n"
			"NumVertices: {}\n"
			"Stride (bytes): {}\n"
			"Type: {}\n",
			m_NumBytes, m_Data, m_NumComponents, m_NumVertices, m_Stride, m_Type));
	}

	auto Attribute::GetNumBytes() const -> GLsizeiptr
	{
		return m_NumBytes;
	}

	auto Attribute::GetData() const -> const void*
	{
		return m_Data;
	}

	auto Attribute::GetNumComponents() const -> GLint
	{
		return m_NumComponents;
	}

	auto Attribute::GetNumVertices() const -> GLuint
	{
		return m_NumVertices;
	}

	auto Attribute::GetStride() const -> GLsizei
	{
		return m_Stride;
	}

	auto Attribute::GetType() const -> GLenum
	{
		return m_Type;
	}

}
