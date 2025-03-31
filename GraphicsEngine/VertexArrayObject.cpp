#include "pch.h"
#include "GraphicsEngine/VertexArrayObject.h"

#include "glm/glm.hpp"

#include "GraphicsEngine/GL.h"

namespace GraphicsEngine
{

	//VertexArrayObject::VertexArrayObject()
	//{
	//	glGenVertexArrays(1, &m_VAO);
	//	if (GL_ERROR())
	//		return;

	//	m_Initialized = true;
	//}

	//VertexArrayObject::operator bool() const
	//{
	//	return m_Initialized;
	//}

	//auto VertexArrayObject::Bind() const -> bool
	//{
	//	if (!m_Initialized)
	//		return false;

	//	glBindVertexArray(m_VAO);
	//	if (GL_ERROR())
	//		return false;

	//	return true;
	//}

	//auto VertexArrayObject::DefineVertexAttribute(unsigned int location, const Buffer& buffer) -> bool
	//{
	//	if (!Bind())
	//	{
	//		LOG_ERROR("Could not bind vao.");
	//		return false;
	//	}

	//	if (!buffer.Bind())
	//	{
	//		LOG_ERROR("Could not bind buffer.");
	//		return false;
	//	}

	//	const auto& dataStore = buffer.GetDataStore();

	//	GLint numComponents;
	//	switch (dataStore.m_NumComponents)
	//	{
	//	case GraphicsEngine::GL::AttributeSize::One:
	//		numComponents = 1;
	//		break;
	//	case GraphicsEngine::GL::AttributeSize::Two:
	//		numComponents = 2;
	//		break;
	//	case GraphicsEngine::GL::AttributeSize::Three:
	//		numComponents = 3;
	//		break;
	//	case GraphicsEngine::GL::AttributeSize::Four:
	//		numComponents = 4;
	//		break;
	//	case GraphicsEngine::GL::AttributeSize::BGRA:
	//		numComponents = GL_BGRA;
	//		break;
	//	default:
	//	{
	//		LOG_ERROR("Unknown attribute size.");
	//		return false;
	//	}
	//	}

	//	GLenum type;
	//	switch (dataStore.m_DataType)
	//	{
	//	case GraphicsEngine::GL::DataType::Byte:
	//		type = GL_BYTE;
	//		break;
	//	case GraphicsEngine::GL::DataType::UnsignedByte:
	//		type = GL_UNSIGNED_BYTE;
	//		break;
	//	case GraphicsEngine::GL::DataType::Short:
	//		type = GL_SHORT;
	//		break;
	//	case GraphicsEngine::GL::DataType::UnsignedShort:
	//		type = GL_UNSIGNED_SHORT;
	//		break;
	//	case GraphicsEngine::GL::DataType::Int:
	//		type = GL_INT;
	//		break;
	//	case GraphicsEngine::GL::DataType::UnsignedInt:
	//		type = GL_UNSIGNED_INT;
	//		break;
	//	case GraphicsEngine::GL::DataType::HalfFloat:
	//		type = GL_HALF_FLOAT;
	//		break;
	//	case GraphicsEngine::GL::DataType::Float:
	//		type = GL_FLOAT;
	//		break;
	//	case GraphicsEngine::GL::DataType::Double:
	//		type = GL_DOUBLE;
	//		break;
	//	case GraphicsEngine::GL::DataType::Int_2_10_10_10_Rev:
	//		type = GL_INT_2_10_10_10_REV;
	//		break;
	//	case GraphicsEngine::GL::DataType::UnsignedInt_2_10_10_10_Rev:
	//		type = GL_UNSIGNED_INT_2_10_10_10_REV;
	//		break;
	//	case GraphicsEngine::GL::DataType::UngisnedInt_10F_11F_11F_Rev:
	//		type = GL_UNSIGNED_INT_10F_11F_11F_REV;
	//		break;
	//	default:
	//	{
	//		LOG_ERROR("Unknown data type.");
	//		return false;
	//	}
	//	}
	//	
	//	glVertexAttribPointer(location, numComponents, type, dataStore.normalized ? GL_TRUE : GL_FALSE, 0, (void*)0);
	//	if (GL_ERROR())
	//		return false;

	//	glEnableVertexAttribArray(location);
	//	if (GL_ERROR())
	//		return false;

	//	return true;
	//}

	//auto VertexArrayObject::GetId() const -> unsigned int
	//{
	//	return m_VAO;
	//}

}
