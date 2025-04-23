#pragma once

#include "IAttribute.h"

namespace GraphicsEngine
{

	class Attribute : public IAttribute
	{
	public:
		explicit Attribute(const std::vector<glm::vec2>& data);
		explicit Attribute(const std::vector<glm::vec3>& data);
		~Attribute() override = default;

		auto GetNumBytes() const -> GLsizeiptr;
		auto GetData() const -> std::vector<std::byte>;
		auto GetNumComponents() const -> GLint;
		auto GetNumVertices() const -> GLuint;
		auto GetStride() const -> GLsizei;
		auto GetType() const -> GLenum;

	private:
		auto LogAttributeCreation() const -> void;

		GLsizeiptr m_NumBytes = 0;
		std::vector<std::byte> m_Data;
		GLint m_NumComponents = 0;
		GLuint m_NumVertices = 0;
		GLsizei m_Stride = 0;
		GLenum m_Type = GL_FLOAT;
	};

	using AttributePtr = std::shared_ptr<Attribute>;

}
