#include "Entity.h"

#include "Attribute.h"
#include "Log.h"
#include "SafeGL.h"

namespace GraphicsEngine
{

	namespace
	{

		struct AttributeData
		{
			GLsizeiptr numBytes = 0;
			std::vector<std::byte> data;
			GLint numComponents = 0;
			GLuint numVertices = 0;
			GLsizei stride = 0;
			GLenum type = GL_FLOAT;
		};

		auto LogAttributeCreation(const AttributeData& attrData) -> void
		{
			GraphicsEngine::GetLog()->Debug(std::format("Created new attribute:\n"
				"NumBytes: {}\n"
				"Data: {}\n"
				"NumComponents: {}\n"
				"NumVertices: {}\n"
				"Stride (bytes): {}\n"
				"Type: {}\n",
				attrData.numBytes, 
				static_cast<const void*>(attrData.data.data()), 
				attrData.numComponents, 
				attrData.numVertices, 
				attrData.stride, 
				attrData.type));
		}

		auto ExtractAttributeData(const std::vector<glm::vec2>& attribute) -> AttributeData
		{
			AttributeData attrData;
			attrData.numBytes = 2 * sizeof(float) * attribute.size();

			attrData.data.resize(attrData.numBytes);
			auto pBegin = glm::value_ptr(*attribute.data());
			memcpy(attrData.data.data(), pBegin, attrData.numBytes);

			attrData.numComponents = 2;
			attrData.numVertices = static_cast<GLuint>(attribute.size());
			attrData.stride = 2 * sizeof(float);
			attrData.type = GL_FLOAT;

			LogAttributeCreation(attrData);

			return attrData;
		}

		auto ExtractAttributeData(const std::vector<glm::vec3>& attribute) -> AttributeData
		{
			AttributeData attrData;
			attrData.numBytes = 3 * sizeof(float) * attribute.size();

			attrData.data.resize(attrData.numBytes);
			auto pBegin = glm::value_ptr(*attribute.data());
			memcpy(attrData.data.data(), pBegin, attrData.numBytes);

			attrData.numComponents = 3;
			attrData.numVertices = static_cast<GLuint>(attribute.size());
			attrData.stride = 3 * sizeof(float);
			attrData.type = GL_FLOAT;

			LogAttributeCreation(attrData);

			return attrData;
		}

	}

	auto InitEntity(const Types::VertexAttributes& attributes, const Types::Indices& indices) -> std::tuple<GLuint, GLsizei, GLsizei>
	{
		size_t numAttributes = attributes.size();

		GLuint vao;
		GL::GenVertexArrays(1, &vao);
		GL::BindVertexArray(vao);

		std::vector<GLuint> buffers(numAttributes);
		GL::GenBuffers(static_cast<GLsizei>(numAttributes), buffers.data());

		GLsizei numVertices = 0;
		for (size_t i = 0; i < numAttributes; ++i)
		{
			AttributeData attrData;
			if (std::holds_alternative<std::vector<glm::vec2> >(attributes[i]))
				attrData = ExtractAttributeData(std::get<std::vector<glm::vec2> >(attributes[i]));
			else if (std::holds_alternative<std::vector<glm::vec3> >(attributes[i]))
				attrData = ExtractAttributeData(std::get<std::vector<glm::vec3> >(attributes[i]));
			
			// We can fill this out from any attribute because we are assuming the caller is 
			// going to provide vertex attributes of equal length.
			numVertices = attrData.numVertices;

			GL::BindBuffer(GL_ARRAY_BUFFER, buffers[i]);
			GL::BufferData(GL_ARRAY_BUFFER, attrData.numBytes, static_cast<const void*>(attrData.data.data()), GL_STATIC_DRAW);
			auto index = static_cast<GLuint>(i);
			GL::VertexAttribPointer(index, attrData.numComponents, attrData.type, GL_FALSE, attrData.stride, nullptr);
			GL::EnableVertexAttribArray(index);
		}

		if (!indices.empty())
		{
			GLuint eboBuffer;
			GL::GenBuffers(1, &eboBuffer);
			GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboBuffer);
			GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		return std::make_tuple(vao, static_cast<GLsizei>(indices.size()), numVertices);
	}

	Entity::Entity(const Types::VertexAttributes& attributes, const Types::Indices& indices)
		: Entity(InitEntity(attributes, indices))
	{
	}

	Entity::Entity(const std::tuple<GLuint, GLsizei, GLsizei>& data)
		:	ENTITY_ID(std::get<0>(data)),
			NUM_INDICES(std::get<1>(data)),
			NUM_VERTICES(std::get<2>(data))
	{
	}

}
