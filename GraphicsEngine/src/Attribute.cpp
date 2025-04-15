#include "pch.h"
#include "Attribute.h"

#include "glm/gtc/type_ptr.hpp"

namespace GraphicsEngine
{

	auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr
	{
		return IAttributePtr(new Attribute(data));
	}

	Attribute::Attribute(const std::vector<glm::vec3>& data)
	{
		m_NumBytes = 3 * sizeof(float) * data.size();
		m_Data = glm::value_ptr(*data.data());
		m_NumComponents = 3;
		m_NumVertices = data.size();
		m_Stride = 3 * sizeof(float);
		m_Type = GL_FLOAT;
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
