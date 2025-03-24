#include "pch.h"
#include "GLUtilities.h"

namespace GraphicsEngine::Utilities
{

	auto BindArrayBuffer(GLuint buffer) -> bool
	{
		return BindBuffer(BufferBindingTarget::Array, buffer);
	}

	auto BindBuffer(BufferBindingTarget target, GLuint buffer) -> bool
	{
		auto logger = spdlog::get("Engine");

		GLenum targetGL = static_cast<GLenum>(target);
		glBindBuffer(targetGL, buffer);
		switch (glGetError())
		{
		case GL_INVALID_ENUM:
			logger->error("target is not one of the allowable values");
			return false;
		case GL_INVALID_VALUE:
			logger->error("buffer is not a name previously returned from a call to glGenBuffers");
			return false;
		}

		return true;
	}

	auto BindVertexArray(GLuint array) -> bool
	{
		glBindVertexArray(array);
		switch (glGetError())
		{
		case GL_INVALID_OPERATION:
			spdlog::get("Engine")->error("array is not zero or the name of a vertex array object previously returned from a call to glGenVertexArrays.");
			return false;
		}

		return true;
	}

	auto BufferData(BufferBindingTarget target, GLsizeiptr size, const void* data, DataUsagePattern usage) -> bool
	{
		auto logger = spdlog::get("Engine");

		GLenum targetGL = static_cast<GLenum>(target);
		GLenum usageGL = static_cast<GLenum>(usage);
		glBufferData(targetGL, size, data, usageGL);
		switch (glGetError())
		{
		case GL_INVALID_ENUM:
			logger->error("target is not one of the accepted buffer targets OR usage is not GL_STREAM_DRAW, "
				"GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, "
				"GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.");
			return false;
		case GL_INVALID_VALUE:
			logger->error("size is negative");
			return false;
		case GL_INVALID_OPERATION:
			logger->error("the reserved buffer object name 0 is bound to target OR "
				"buffer is not the name of an existing buffer object OR "
				"the GL_BUFFER_IMMUTABLE_STORAGE flag of the buffer object is GL_TRUE.");
			return false;
		case GL_OUT_OF_MEMORY:
			logger->error("the GL is unable to create a data store with the specified size.");
			return false;
		}

		return true;
	}

	auto BufferFloatData(BufferBindingTarget target, const std::vector<float>& data, DataUsagePattern usage) -> bool
	{
		return BufferData(target, data.size() * sizeof(float), data.data(), usage);
	}

	auto EnableVertexAttribArray(GLuint index) -> bool
	{
		auto logger = spdlog::get("Engine");
		glEnableVertexAttribArray(index);
		switch (glGetError())
		{
		case GL_INVALID_OPERATION:
			logger->error("no vertex array object is bound "
				"OR vaobj is not the name of an existing vertex array object.");
			return false;
		case GL_INVALID_VALUE:
			logger->error("index is greater than or equal to GL_MAX_VERTEX_ATTRIBS.");
			return false;
		}

		return true;
	}

	auto GenBuffers(GLsizei n) -> std::vector<GLuint>
	{
		std::vector<GLuint> buffers(n);
		glGenBuffers(n, buffers.data());
		switch (glGetError())
		{
		case GL_INVALID_VALUE:
			spdlog::get("Engine")->error("n is negative");
			return {};
		}

		return buffers;
	}

	auto GenOneBuffer() -> std::optional<GLuint>
	{
		auto buffers = GenBuffers(1);
		if (buffers.empty())
		{
			spdlog::get("Engine")->error("GenBuffers returned empty vector.");
			return std::nullopt;
		}

		return buffers.front();
	}

	auto GenOneVertexArray() -> std::optional<GLuint>
	{
		auto VAOs = GenVertexArrays(1);
		if (VAOs.empty())
		{
			spdlog::get("Engine")->error("GenVertexArrays returned empty vector.");
			return std::nullopt;
		}

		return VAOs.front();
	}

	auto GenVertexArrays(GLsizei n) -> std::vector<GLuint>
	{
		std::vector<GLuint> VAOs(n);
		glGenVertexArrays(n, VAOs.data());
		switch (glGetError())
		{
		case GL_INVALID_VALUE:
			spdlog::get("Engine")->error("n is negative.");
			return {};
		}

		return VAOs;
	}

	auto UnbindArrayBuffer() -> bool
	{
		return UnbindBuffer(BufferBindingTarget::Array);
	}

	auto UnbindBuffer(BufferBindingTarget target) -> bool
	{
		return BindBuffer(target, 0);
	}

	auto UnbindVertexArray() -> bool
	{
		return BindVertexArray(0);
	}

	auto VertexAttribPointer(GLuint index, AttributeSize size, DataType type, bool normalized, GLsizei stride, int offsetOfFirstComponent) -> bool
	{
		auto logger = spdlog::get("Engine");

		GLint sizeGL = static_cast<GLint>(size);
		GLenum typeGL = static_cast<GLenum>(type);
		GLboolean normalizedGL = normalized ? GL_TRUE : GL_FALSE;
		void* offsetOfFirstComponentGL = (void*)offsetOfFirstComponent;
		glVertexAttribPointer(index, sizeGL, typeGL, normalizedGL, stride, offsetOfFirstComponentGL);
		switch (glGetError())
		{
		case GL_INVALID_VALUE:
			logger->error("index is greater than or equal to GL_MAX_VERTEX_ATTRIBS OR"
				"size is not 1, 2, 3, 4 or (for glVertexAttribPointer), GL_BGRA OR"
				"stride is negative.");
			return false;
		case GL_INVALID_ENUM:
			logger->error("type is not an accepted value.");
			return false;
		case GL_INVALID_OPERATION:
			logger->error("size is GL_BGRA and type is not GL_UNSIGNED_BYTE, GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV OR"
				"type is GL_INT_2_10_10_10_REV or GL_UNSIGNED_INT_2_10_10_10_REV and size is not 4 or GL_BGRA OR"
				"type is GL_UNSIGNED_INT_10F_11F_11F_REV and size is not 3 OR"
				"size is GL_BGRA and normalized is GL_FALSE OR"
				"zero is bound to the GL_ARRAY_BUFFER buffer object binding point and the pointer argument is not NULL.");
			return false;
		}

		return true;
	}

}
