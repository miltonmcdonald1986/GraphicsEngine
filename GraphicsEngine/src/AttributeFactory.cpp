#include "AttributeFactory.h"

namespace GraphicsEngine::AttributeFactory::Triangle
{

	namespace Helpers
	{

		static auto CenterTriangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2);
		static auto ComputeCentroid(const std::vector<glm::vec3>& vertices) -> std::optional<glm::vec3>;
		static auto ValidTriangle(float a, float b, float c) -> bool;

		static auto CenterTriangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2)
		{
			auto centroid = *ComputeCentroid({ v0, v1, v2 });
			for (auto v : { &v0, &v1, &v2 })
			{
				*v -= centroid;
			}
		}

		static auto ComputeCentroid(const std::vector<glm::vec3>& vertices) -> std::optional<glm::vec3>
		{
			if (vertices.empty())
				return std::nullopt;

			return std::accumulate(vertices.begin(), vertices.end(), glm::vec3(0.f, 0.f, 0.f)) / static_cast<float>(vertices.size());
		}

		static auto ValidTriangle(float a, float b, float c) -> bool
		{
			return (a + b > c) && (a + c > b) && (b + c > a);
		}

	}

	auto AAS(float A, float B, float a) -> GraphicsEngine::IAttributePtr
	{
		if (A <= 0.f || B <= 0.f)
			return nullptr;

		if (a <= 0.f)
			return nullptr;

		if (A + B >= std::numbers::pi_v<float>)
			return nullptr;

		glm::vec3 v0(0.f, 0.f, 0.f);
		
		float b = a * std::sin(B) / std::sin(A);
		float c0 = b * std::cos(A);
		float c1 = a * std::cos(B);
		float c = c0 + c1;
		glm::vec3 v1(c, 0.f, 0.f);
		glm::vec3 v2(c0, a * std::sin(B), 0.f);

		Helpers::CenterTriangle(v0, v1, v2);

		return GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{ v0, v1, v2 });
	}

	auto ASA(float A, float c, float B) -> GraphicsEngine::IAttributePtr
	{
		if (A <= 0.f || B <= 0.f)
			return nullptr;

		if (c <= 0.f)
			return nullptr;

		if (A + B >= std::numbers::pi_v<float>)
			return nullptr;

		glm::vec3 v0(0.f, 0.f, 0.f);
		glm::vec3 v1(c, 0.f, 0.f);
		
		float C = std::numbers::pi_v<float> - A - B;
		float a = c * std::sin(A) / std::sin(C);
		float x = c - a * std::cos(B);
		float y = a * std::sin(B);
		glm::vec3 v2(x, y, 0.f);

		Helpers::CenterTriangle(v0, v1, v2);

		return GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{ v0, v1, v2 });
	}

	auto HL(float hypotenuse, float leg) -> GraphicsEngine::IAttributePtr
	{
		if (hypotenuse <= 0.f || leg <= 0.f)
			return nullptr;

		if (hypotenuse <= leg)
			return nullptr;

		glm::vec3 v0(0.f, 0.f, 0.f);
		glm::vec3 v1(leg, 0.f, 0.f);
		glm::vec3 v2(0.f, std::sqrt(std::pow(hypotenuse, 2.f) - std::pow(leg, 2.f)), 0.f);

		Helpers::CenterTriangle(v0, v1, v2);

		return GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{ v0, v1, v2 });
	}

	auto SAS(float a, float C, float b) -> GraphicsEngine::IAttributePtr
	{
		if (a <= 0.f || b <= 0.f)
			return nullptr;

		if (C <= 0.f || C >= std::numbers::pi_v<float>)
			return nullptr;

		glm::vec3 v0(0.f, 0.f, 0.f);
		glm::vec3 v1(a, 0.f, 0.f);

		float y = b * std::sin(C);
		float x = a - b * std::cos(C);
		glm::vec3 v2(x, y, 0.f);

		Helpers::CenterTriangle(v0, v1, v2);

		return GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{ v0, v1, v2 });
	}

	auto SSS(float a, float b, float c) -> GraphicsEngine::IAttributePtr
	{
		if (!Helpers::ValidTriangle(a, b, c))
			return nullptr;

		glm::vec3 v0(0.f, 0.f, 0.f);
		glm::vec3 v1(c, 0.f, 0.f);

		float x = (std::pow(a, 2.f) - std::pow(b, 2.f) + std::pow(c, 2.f) / (2.f * c));
		float y = std::sqrt(std::pow(a, 2.f) - std::pow((std::pow(a, 2.f) - std::pow(b, 2.f) + std::pow(c, 2.f)) / (2.f * c), 2.f));
		glm::vec3 v2(x, y, 0.f);

		auto centroid = *Helpers::ComputeCentroid({ v0, v1, v2 });
		for (auto v : { &v0, &v1, &v2 })
		{
			*v -= centroid;
		}

		return GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{ v0, v1, v2 });
	}

}
