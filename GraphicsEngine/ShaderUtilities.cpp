#include "pch.h"
#include "GLUtilities.h"
#include "ShaderUtilities.h"

#include <fstream>

#include "spdlog/spdlog.h"

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

namespace GraphicsEngine::Utilities
{

	auto CompileFragmentShader(const std::filesystem::path& path) -> std::optional<GLuint>
	{
		return CompileFragmentShader(ReadFile(path));
	}

	auto CompileFragmentShader(const std::string& source) -> std::optional<GLuint>
	{
		return CompileShader(GL::Utilities::ShaderType::Fragment, source);
	}

	auto CompileShader(GL::Utilities::ShaderType shaderType, const std::string& source) -> std::optional<GLuint>
	{
		auto optShader = CreateShader(shaderType);
		if (!optShader)
			return std::nullopt;

		GLuint shader = *optShader;

		if (!GL::Utilities::ShaderSource(shader, { source }))
			return std::nullopt;

		if (!GL::Utilities::CompileShader(shader))
			return std::nullopt;

		return shader;
	}

	auto CompileVertexShader(const std::filesystem::path& path) -> std::optional<GLuint>
	{
		return CompileVertexShader(ReadFile(path));
	}

	auto CompileVertexShader(const std::string& source) -> std::optional<GLuint>
	{
		return CompileShader(GL::Utilities::ShaderType::Vertex, source);
	}

	auto LinkProgram(const std::vector<GLuint>& shaders) -> std::optional<GLuint>
	{
		auto logger = spdlog::get("Engine");

		auto optProgram = GL::Utilities::CreateProgram();
		if (!optProgram)
			return std::nullopt;

		auto shaderProgram = *optProgram;

		for (auto shader : shaders)
		{
			if (!GL::Utilities::AttachShader(shaderProgram, shader))
				return std::nullopt;
		}
		
		if (!GL::Utilities::LinkProgram(shaderProgram))
			return std::nullopt;

		for (auto shader : shaders)
		{
			if (!GL::Utilities::DeleteShader(shader))
				spdlog::get("Engine")->warn(std::format("{}\t{}\t{}\t{}", std::filesystem::path(__FILE__).filename().string(), __func__, __LINE__, "DeleteShader returned false."));
		}

		return shaderProgram;
	}

	auto ShaderIsDeleted(GLuint shader) -> std::optional<bool>
	{
		return GL::Utilities::GetShaderDeleteStatus(shader);
	}

}
