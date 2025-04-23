#include "Attribute.h"

#include "Log.h"

namespace GraphicsEngine
{

	auto CreateAttribute(const std::vector<glm::vec2>& data) -> IAttributePtr
	{
		return std::make_shared<Attribute>(data);
	}

	auto CreateAttribute(const std::vector<glm::vec3>& data) -> IAttributePtr
	{
		return std::make_shared<Attribute>(data);
	}

	Attribute::Attribute(const std::vector<glm::vec2>& data)
	{
		m_NumBytes = 2 * sizeof(float) * data.size();

		m_Data.resize(m_NumBytes);
		auto pBegin = glm::value_ptr(*data.data());
		memcpy(m_Data.data(), reinterpret_cast<const std::byte*>(pBegin), m_NumBytes);

		m_NumComponents = 2;
		m_NumVertices = static_cast<GLuint>(data.size());
		m_Stride = 2 * sizeof(float);
		m_Type = GL_FLOAT;

		LogAttributeCreation();
	}

	Attribute::Attribute(const std::vector<glm::vec3>& data)
	{
		m_NumBytes = 3 * sizeof(float) * data.size();
		
		m_Data.resize(m_NumBytes);
		auto pBegin = glm::value_ptr(*data.data());
		memcpy(m_Data.data(), reinterpret_cast<const std::byte*>(pBegin), m_NumBytes);
		
		m_NumComponents = 3;
		m_NumVertices = static_cast<GLuint>(data.size());
		m_Stride = 3 * sizeof(float);
		m_Type = GL_FLOAT;

		LogAttributeCreation();
	}

	auto Attribute::GetNumBytes() const -> GLsizeiptr
	{
		return m_NumBytes;
	}

	auto Attribute::GetData() const -> std::vector<std::byte>
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

	auto Attribute::LogAttributeCreation() const -> void
	{
		GetLog()->Debug(std::format("Created new attribute:\n"
			"NumBytes: {}\n"
			"Data: {}\n"
			"NumComponents: {}\n"
			"NumVertices: {}\n"
			"Stride (bytes): {}\n"
			"Type: {}\n",
			m_NumBytes, static_cast<const void*>(m_Data.data()), m_NumComponents, m_NumVertices, m_Stride, m_Type));
	}

}
