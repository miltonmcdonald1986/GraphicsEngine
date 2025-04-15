#pragma once

#include "IAttribute.h"

namespace GraphicsEngine
{

	class Attribute : public IAttribute
	{
	public:
		Attribute(const std::vector<glm::vec3>& data);
		virtual ~Attribute() override = default;

		auto GetNumBytes() const -> GLsizeiptr;
		auto GetData() const -> const void*;
		auto GetNumComponents() const -> GLint;
		auto GetNumVertices() const -> GLuint;
		auto GetStride() const -> GLsizei;
		auto GetType() const -> GLenum;

	private:
		GLsizeiptr m_NumBytes = 0;
		const void* m_Data = nullptr;
		GLint m_NumComponents = 0;
		GLuint m_NumVertices = 0;
		GLsizei m_Stride = 0;
		GLenum m_Type = GL_FLOAT;
	};

}
