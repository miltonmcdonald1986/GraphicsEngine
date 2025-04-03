#include "pch.h"
#include "GraphicsEngine/Shader.h"

#include "GraphicsEngine/GL.h"

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

	auto CompileShader(GLenum shaderType, const std::string& source) -> std::optional<GLuint>
	{
		GLuint shader = 0;
		switch (shaderType)
		{
		case GL_FRAGMENT_SHADER:
			shader = GraphicsEngine::GL::CreateFragmentShader();
			break;
		case GL_GEOMETRY_SHADER:
			shader = GraphicsEngine::GL::CreateGeometryShader();
			break;
		case GL_VERTEX_SHADER:
			shader = GraphicsEngine::GL::CreateVertexShader();
			break;
		}

		std::vector<const char*> strings;
		strings.push_back(source.c_str());

		GraphicsEngine::GL::ShaderSource(shader, static_cast<int>(strings.size()), strings.data(), nullptr);
		GraphicsEngine::GL::CompileShader(shader);
		bool success = GraphicsEngine::GL::GetCompileStatus(shader);
		if (!success)
		{
			char infoLog[512];
			GraphicsEngine::GL::GetShaderInfoLog(shader, 512, NULL, infoLog);
			spdlog::get("Engine")->error(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, infoLog));
			return std::nullopt;
		}

		return shader;
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

		GLuint shaderProgram = GL::CreateProgram();
		for (auto shader : shaders)
		{
			GL::AttachShader(shaderProgram, shader);
		}
		
		glLinkProgram(shaderProgram);

		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			return false;
		}

		for (auto shader : shaders)
		{
			glDeleteShader(shader);
		}

		return shaderProgram;
	}

}
