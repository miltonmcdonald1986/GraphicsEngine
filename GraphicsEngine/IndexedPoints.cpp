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

		GLuint vao;
		glGenVertexArrays(1, &vao);
		if (GL_ERROR())
			return std::nullopt;
		
		glBindVertexArray(vao);
		if (GL_ERROR())
			return std::nullopt;

		// Generate and bind a buffer for the vertices, and fill it with data.

		GLuint vbo;
		glGenBuffers(1, &vbo);
		if (GL_ERROR())
			return std::nullopt;
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		if (GL_ERROR())
			return std::nullopt;
		
		glBufferData(GL_ARRAY_BUFFER, verticesData.size() * sizeof(float), verticesData.data(), GL_STATIC_DRAW);
		if (GL_ERROR())
			return std::nullopt;

		// Specify the layout of the only vertex attribute (position), and enable that attribute.

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
		if (GL_ERROR())
			return std::nullopt;

		glEnableVertexAttribArray(0);
		if (GL_ERROR())
			return std::nullopt;

		// Generate and bind a buffer for the indices, and fill it with data.

		GLuint ebo;
		glGenBuffers(1, &ebo);
		if (GL_ERROR())
			return std::nullopt;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		if (GL_ERROR())
			return std::nullopt;
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
		if (GL_ERROR())
			return std::nullopt;

		return vao;
	}

}