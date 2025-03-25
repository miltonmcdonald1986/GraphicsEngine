#include "pch.h"
#include "GLUtilities.h"

#include <filesystem>

#include "spdlog/spdlog.h"

#define GL_ERROR() GetError(__FILE__, __func__, __LINE__) != ErrorFlag::NoError

namespace GraphicsEngine::Utilities
{
	auto AttachShader(GLuint program, GLuint shader) -> bool
	{
		glAttachShader(program, shader);
		if (GL_ERROR())
			return false;

		return true;
	}

	auto BindArrayBuffer(GLuint buffer) -> bool
	{
		return BindBuffer(BufferBindingTarget::Array, buffer);
	}

	auto BindBuffer(BufferBindingTarget target, GLuint buffer) -> bool
	{
		auto logger = spdlog::get("Engine");

		GLenum targetGL = static_cast<GLenum>(target);
		glBindBuffer(targetGL, buffer);
		if (GL_ERROR())
			return false;

		return true;
	}

	auto BindVertexArray(GLuint array) -> bool
	{
		glBindVertexArray(array);
		if (GL_ERROR())
			return false;

		return true;
	}

	auto BufferData(BufferBindingTarget target, GLsizeiptr size, const void* data, DataUsagePattern usage) -> bool
	{
		auto logger = spdlog::get("Engine");

		GLenum targetGL = static_cast<GLenum>(target);
		GLenum usageGL = static_cast<GLenum>(usage);
		glBufferData(targetGL, size, data, usageGL);
		if (GL_ERROR())
			return false;

		return true;
	}

	auto BufferFloatData(BufferBindingTarget target, const std::vector<float>& data, DataUsagePattern usage) -> bool
	{
		return BufferData(target, data.size() * sizeof(float), data.data(), usage);
	}

	auto ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -> void
	{
		glClearColor(red, green, blue, alpha);
	}

	auto ClearColorBuffers() -> bool
	{
		glClear(GL_COLOR_BUFFER_BIT);
		if (GL_ERROR())
			return false;

		return true;
	}

	auto CompileShader(GLuint shader) -> bool
	{
		glCompileShader(shader);
		if (GL_ERROR())
			return false;

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (GL_ERROR())
			return false;

		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			GetError(__FILE__, __func__, __LINE__);
			spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
			return false;
		}

		return true;
	}

	auto CreateProgram() -> std::optional<GLuint>
	{
		GLuint shaderProgram = glCreateProgram();
		if (shaderProgram == 0)
		{
			spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, "An error occurred creating the program object."));
			return std::nullopt;
		}

		return shaderProgram;
	}

	auto CreateShader(ShaderType type) -> std::optional<GLuint>
	{
		auto logger = spdlog::get("Engine");

		GLuint shader = glCreateShader(static_cast<GLenum>(type));
		if (GL_ERROR())
			return std::nullopt;

		return shader;
	}

	GRAPHICSENGINE_API auto DeleteShader(GLuint shader) -> bool
	{
		glDeleteShader(shader);
		if (GL_ERROR())
			return false;
		
		return true;
	}

	auto EnableVertexAttribArray(GLuint index) -> bool
	{
		auto logger = spdlog::get("Engine");
		glEnableVertexAttribArray(index);
		if (GL_ERROR())
			return false;

		return true;
	}

	auto GenBuffers(GLsizei n) -> std::vector<GLuint>
	{
		std::vector<GLuint> buffers(n);
		glGenBuffers(n, buffers.data());
		if (GL_ERROR())
			return {};

		return buffers;
	}

	auto GenOneBuffer() -> std::optional<GLuint>
	{
		auto buffers = GenBuffers(1);
		if (buffers.empty())
			return std::nullopt;

		return buffers.front();
	}

	auto GenOneVertexArray() -> std::optional<GLuint>
	{
		auto VAOs = GenVertexArrays(1);
		if (VAOs.empty())
			return std::nullopt;

		return VAOs.front();
	}

	auto GenVertexArrays(GLsizei n) -> std::vector<GLuint>
	{
		std::vector<GLuint> VAOs(n);
		glGenVertexArrays(n, VAOs.data());
		if (GL_ERROR())
			return {};

		return VAOs;
	}

	auto GetColorClearValue() -> std::optional<std::array<float, 4>>
	{
		float data[4];
		glGetFloatv(GL_COLOR_CLEAR_VALUE, data);
		if (GL_ERROR())
			return std::nullopt;

		return std::array<float, 4> { data[0], data[1], data[2], data[3] };
	}

	auto GetError(const char* file, const char* function, int line) -> ErrorFlag
	{
		auto filename = std::filesystem::path(file).filename().string();

		const auto formatMsg = "{}\t{}\t{}\t{}";
		const std::map<ErrorFlag, std::string> errorMsgMap = {
			{ ErrorFlag::NoError, "No error has been recorded." },
			{ ErrorFlag::InvalidEnum,  "An unacceptable value is specified for an enumerated argument." },
			{ ErrorFlag::InvalidValue, "A numeric argument is out of range." },
			{ ErrorFlag::InvalidOperation, "The specified operation is not allowed in the current state." },
			{ ErrorFlag::InvalidFramebufferOperation, "The framebuffer object is not complete." },
			{ ErrorFlag::OutOfMemory, "There is not enough memory left to execute the command." }};

		auto logger = spdlog::get("Engine");
		ErrorFlag flag = static_cast<ErrorFlag>(glGetError());
		auto errorMsg = errorMsgMap.at(flag);
		switch (flag)
		{
		case GraphicsEngine::Utilities::ErrorFlag::NoError:
			logger->trace(std::format(formatMsg, filename, function, line, errorMsg));
			break;
		case GraphicsEngine::Utilities::ErrorFlag::InvalidEnum:
		case GraphicsEngine::Utilities::ErrorFlag::InvalidValue:
		case GraphicsEngine::Utilities::ErrorFlag::InvalidOperation:
		case GraphicsEngine::Utilities::ErrorFlag::InvalidFramebufferOperation:
		case GraphicsEngine::Utilities::ErrorFlag::OutOfMemory:
			logger->error(std::format(formatMsg, filename, function, line, errorMsg));
			break;
		default:
			logger->warn(std::format(formatMsg, filename, function, line, "Unknown error flag."));
			break;
		}

		return flag;
	}

	auto GetShaderDeleteStatus(GLuint shader) -> std::optional<bool>
	{
		auto logger = spdlog::get("Engine");

		GLint param;
		glGetShaderiv(shader, GL_DELETE_STATUS, &param);
		if (GL_ERROR())
			return std::nullopt;
		
		return (param == GL_TRUE) ? true : false;
	}

	auto LinkProgram(GLuint program) -> bool
	{
		glLinkProgram(program);
		if (GL_ERROR())
			return false;

		int success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (GL_ERROR())
			return false;

		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			GetError(__FILE__, __func__, __LINE__);
			spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
			return false;
		}

		return true;
	}

	auto ShaderSource(GLuint shader, const std::vector<std::string>& sources) -> bool
	{
		std::vector<const GLchar*> strings;
		for (const auto &source : sources)
		{
			strings.push_back(source.c_str());
		}

		glShaderSource(shader, static_cast<GLsizei>(sources.size()), strings.data(), nullptr);
		if (GL_ERROR())
			return false;

		return true;
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
		if (GL_ERROR())
			return false;

		return true;
	}

}
