#include "pch.h"
#include "GraphicsEngine/GL.h"
#include "GraphicsEngine/Shader.h"

#include <fstream>

#include "spdlog/spdlog.h"

#include "GraphicsEngine/Log.h"

namespace 
{

	std::string ReadFile(const std::filesystem::path& path)
	{
		std::ifstream ifs(path);
		std::stringstream buffer;
		buffer << ifs.rdbuf();

		std::string str(buffer.str());
		return str;
	}

}

namespace GraphicsEngine::Shader
{

	auto CompileFragmentShader(const std::filesystem::path& path) -> std::optional<GLuint>
	{
		return CompileFragmentShader(ReadFile(path));
	}

	auto CompileFragmentShader(const std::string& source) -> std::optional<GLuint>
	{
		return CompileShader(GL_FRAGMENT_SHADER, source);
	}

	auto CompileShader(GLenum shaderType, const std::string& source) -> std::optional<GLuint>
	{		
		auto shader = glCreateShader(shaderType);
		if (shader == 0)
		{
			LOG_ERROR("An error occurred creating the shader object.");
			return std::nullopt;
		}
		if (GL_ERROR())
			return std::nullopt;
		

		std::vector<const GLchar*> strings;
		strings.push_back(source.c_str());

		glShaderSource(shader, static_cast<GLsizei>(strings.size()), strings.data(), nullptr);
		if (GL_ERROR())
			return std::nullopt;

		glCompileShader(shader);
		if (GL_ERROR())
			return std::nullopt;

		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (GL_ERROR())
			return std::nullopt;

		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			GL_ERROR();
			spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
			return std::nullopt;
		}

		return shader;
	}

	auto CompileVertexShader(const std::filesystem::path& path) -> std::optional<GLuint>
	{
		return CompileVertexShader(ReadFile(path));
	}

	auto CompileVertexShader(const std::string& source) -> std::optional<GLuint>
	{
		return CompileShader(GL_VERTEX_SHADER, source);
	}

	auto LinkProgram(const std::vector<GLuint>& shaders) -> std::optional<GLuint>
	{
		auto logger = spdlog::get("Engine");

		GLuint shaderProgram = glCreateProgram();
		if (shaderProgram == 0)
		{
			spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, "An error occurred creating the program object."));
			return std::nullopt;
		}

		for (auto shader : shaders)
		{
			glAttachShader(shaderProgram, shader);
			if (GL_ERROR())
				return std::nullopt;
		}
		
		glLinkProgram(shaderProgram);
		if (GL_ERROR())
			return false;

		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (GL_ERROR())
			return false;

		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			GL_ERROR();
			return false;
		}

		for (auto shader : shaders)
		{
			glDeleteShader(shader);
			GL_ERROR();
		}

		return shaderProgram;
	}

	auto ShaderIsDeleted(GLuint shader) -> std::optional<bool>
	{
		GLint param;
		glGetShaderiv(shader, GL_DELETE_STATUS, &param);
		if (GL_ERROR())
			return std::nullopt;

		return (param == GL_TRUE) ? true : false;
	}

}
