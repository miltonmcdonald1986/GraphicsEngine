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

	auto SAS(float a, float C, float b) -> GraphicsEngine::IAttributePtr
	{
		if (C <= 0.f || C >= std::numbers::pi_v<float>)
			return nullptr;

		glm::vec3 v0(0.f, 0.f, 0.f);
		glm::vec3 v1(a, 0.f, 0.f);

		float y = b * std::sinf(C);
		float x = a - b * std::cosf(C);
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

		float x = (std::powf(a, 2.f) - std::powf(b, 2.f) + std::powf(c, 2.f) / (2.f * c));
		float y = std::sqrtf(std::powf(a, 2.f) - std::powf((std::powf(a, 2.f) - std::powf(b, 2.f) + std::powf(c, 2.f)) / (2.f * c), 2.f));
		glm::vec3 v2(x, y, 0.f);

		auto centroid = *Helpers::ComputeCentroid({ v0, v1, v2 });
		for (auto v : { &v0, &v1, &v2 })
		{
			*v -= centroid;
		}

		return GraphicsEngine::CreateAttribute(std::vector<glm::vec3>{ v0, v1, v2 });
	}

}
