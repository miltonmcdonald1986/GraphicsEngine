#include "pch.h"
#include "GraphicsEngine/IndexedPoints.h"

#include <iterator>

#include "GraphicsEngine/GL.h"

namespace GraphicsEngine
{

	auto AddIndexedPoints(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices) -> std::optional<GLuint>
	{
		std::vector<float> verticesData;
		for (const auto& vertex : vertices)
		{
			verticesData.push_back(vertex.x);
			verticesData.push_back(vertex.y);
			verticesData.push_back(vertex.z);
		}

		// Generate and bind the vertex array object.

		std::optional<GLuint> optVAO = GL::GenOneVertexArray();
		if (!optVAO)
			return std::nullopt;

		GLuint vao = *optVAO;

		if (!GL::BindVertexArray(vao))
			return std::nullopt;

		// Generate and bind a buffer for the vertices, and fill it with data.

		std::optional<GLuint> optVBO = GL::GenOneBuffer();
		if (!optVBO)
			return std::nullopt;

		GLuint vbo = *optVBO;

		if (!GL::BindArrayBuffer(vbo))
			return std::nullopt;

		if (!GL::BufferFloatData(GL::BufferBindingTarget::Array, verticesData, GL::DataUsagePattern::StaticDraw))
			return std::nullopt;

		// Specify the layout of the only vertex attribute (position), and enable that attribute.

		if (!GL::VertexAttribPointer(0, GL::AttributeSize::Three, GL::DataType::Float, false, 3 * sizeof(float), 0))
			return std::nullopt;

		if (!GL::EnableVertexAttribArray(0))
			return std::nullopt;

		// Generate and bind a buffer for the indices, and fill it with data.

		std::optional<GLuint> optEBO = GL::GenOneBuffer();
		if (!optEBO)
			return std::nullopt;

		GLuint ebo = *optEBO;

		if (!GL::BindElementArrayBuffer(ebo))
			return std::nullopt;

		if (!GL::BufferUnsignedIntData(GL::BufferBindingTarget::ElementArray, indices, GL::DataUsagePattern::StaticDraw))
			return std::nullopt;

		return vao;
	}

}