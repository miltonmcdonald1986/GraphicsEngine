#include "Entity.h"

#include "Attribute.h"
#include "SafeGL.h"

namespace GraphicsEngine
{

	auto InitEntity(const IAttributes& attributes, const Indices& indices) -> std::tuple<GLuint, GLsizei, GLsizei>
	{
		size_t numAttributes = attributes.size();

		GLuint vao;
		GL::GenVertexArrays(1, &vao);
		GL::BindVertexArray(vao);

		std::vector<GLuint> buffers(numAttributes);
		GL::GenBuffers(static_cast<GLsizei>(numAttributes), buffers.data());

		for (size_t i = 0; i < numAttributes; ++i)
		{
			AttributePtr spAttribute = std::dynamic_pointer_cast<Attribute>(attributes[i]);
			GL::BindBuffer(GL_ARRAY_BUFFER, buffers[i]);
			GL::BufferData(GL_ARRAY_BUFFER, spAttribute->GetNumBytes(), static_cast<const void*>(spAttribute->GetData().data()), GL_STATIC_DRAW);
			auto index = static_cast<GLuint>(i);
			GL::VertexAttribPointer(index, spAttribute->GetNumComponents(), spAttribute->GetType(), GL_FALSE, spAttribute->GetStride(), nullptr);
			GL::EnableVertexAttribArray(index);
		}

		if (!indices.empty())
		{
			GLuint eboBuffer;
			GL::GenBuffers(1, &eboBuffer);
			GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboBuffer);
			GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		return std::make_tuple(vao, static_cast<GLsizei>(indices.size()), std::dynamic_pointer_cast<Attribute>(attributes[0])->GetNumVertices());
	}

	Entity::Entity(const IAttributes& attributes, const Indices& indices)
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
