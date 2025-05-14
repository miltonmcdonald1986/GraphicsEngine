#include "AttributeFactory.h"

namespace GraphicsEngine::AttributeFactory
{

	namespace Cube
	{

		auto TextureCoordinates() -> Types::VertexAttribute
		{
			// Each face has four texture coordinates, which we apply in counterclockwise order.
			auto t0 = glm::vec2(0.f, 0.f);
			auto t1 = glm::vec2(1.f, 0.f);
			auto t2 = glm::vec2(1.f, 1.f);
			auto t3 = glm::vec2(0.f, 1.f);

			// Associate each face to the texture coordinates
			return std::vector<glm::vec2>{
				t0, t1, t2, t3, // FACE 0
				t0, t1, t2, t3, // FACE 1
				t0, t1, t2, t3, // FACE 2
				t0, t1, t2, t3, // FACE 3
				t0, t1, t2, t3, // FACE 4
				t0, t1, t2, t3  // FACE 5
			};
		}

		auto Position() -> Types::VertexAttribute
		{
			// A cube has eight vertices
			auto v0 = glm::vec3(-0.5f, -0.5f, 0.5f);
			auto v1 = glm::vec3(0.5f, -0.5f, 0.5f);
			auto v2 = glm::vec3(0.5f, 0.5f, 0.5f);
			auto v3 = glm::vec3(-0.5f, 0.5f, 0.5f);
			auto v4 = glm::vec3(0.5f, -0.5f, -0.5f);
			auto v5 = glm::vec3(0.5f, 0.5f, -0.5f);
			auto v6 = glm::vec3(-0.5f, -0.5f, -0.5f);
			auto v7 = glm::vec3(-0.5f, 0.5f, -0.5f);

			// A cube has six faces
			return  std::vector<glm::vec3>{
				v0, v1, v2, v3, // FACE 0
				v1, v4, v5, v2, // FACE 1
				v4, v6, v7, v5, // FACE 2
				v6, v0, v3, v7, // FACE 3
				v6, v4, v1, v0, // FACE 4
				v3, v2, v5, v7  // FACE 5
			};
		}

	}

	namespace Triangle
	{

		namespace Helpers
		{

			static auto CenterTriangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2) -> void;
			static auto ComputeCentroid(const std::vector<glm::vec3>& vertices) -> std::optional<glm::vec3>;
			static auto ValidTriangle(float a, float b, float c) -> bool;

			static auto CenterTriangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2) -> void
			{
				auto oCentroid = ComputeCentroid({ v0, v1, v2 });
				if (!oCentroid)
					return;

				for (auto v : { &v0, &v1, &v2 })
				{
					*v -= *oCentroid;
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

		auto AAS(float A, float B, float a) -> Types::VertexAttribute
		{
			if (A <= 0.f || B <= 0.f)
				return {};

			if (a <= 0.f)
				return {};

			if (A + B >= std::numbers::pi_v<float>)
				return {};

			glm::vec3 v0(0.f, 0.f, 0.f);

			float b = a * std::sin(B) / std::sin(A);
			float c0 = b * std::cos(A);
			float c1 = a * std::cos(B);
			float c = c0 + c1;
			glm::vec3 v1(c, 0.f, 0.f);
			glm::vec3 v2(c0, a * std::sin(B), 0.f);

			Helpers::CenterTriangle(v0, v1, v2);

			return std::vector<glm::vec3>{ v0, v1, v2 };
		}

		auto ASA(float A, float c, float B) -> Types::VertexAttribute
		{
			if (A <= 0.f || B <= 0.f)
				return {};

			if (c <= 0.f)
				return {};

			if (A + B >= std::numbers::pi_v<float>)
				return {};

			glm::vec3 v0(0.f, 0.f, 0.f);
			glm::vec3 v1(c, 0.f, 0.f);

			float C = std::numbers::pi_v<float> - A - B;
			float a = c * std::sin(A) / std::sin(C);
			float x = c - a * std::cos(B);
			float y = a * std::sin(B);
			glm::vec3 v2(x, y, 0.f);

			Helpers::CenterTriangle(v0, v1, v2);

			return std::vector<glm::vec3>{ v0, v1, v2 };
		}

		auto HL(float hypotenuse, float leg) -> Types::VertexAttribute
		{
			if (hypotenuse <= 0.f || leg <= 0.f)
				return {};

			if (hypotenuse <= leg)
				return {};

			glm::vec3 v0(0.f, 0.f, 0.f);
			glm::vec3 v1(leg, 0.f, 0.f);
			glm::vec3 v2(0.f, std::sqrt(std::pow(hypotenuse, 2.f) - std::pow(leg, 2.f)), 0.f);

			Helpers::CenterTriangle(v0, v1, v2);

			return std::vector<glm::vec3>{ v0, v1, v2 };
		}

		auto SAS(float a, float C, float b) -> Types::VertexAttribute
		{
			if (a <= 0.f || b <= 0.f)
				return {};

			if (C <= 0.f || C >= std::numbers::pi_v<float>)
				return {};

			glm::vec3 v0(0.f, 0.f, 0.f);
			glm::vec3 v1(a, 0.f, 0.f);

			float y = b * std::sin(C);
			float x = a - b * std::cos(C);
			glm::vec3 v2(x, y, 0.f);

			Helpers::CenterTriangle(v0, v1, v2);

			return std::vector<glm::vec3>{ v0, v1, v2 };
		}

		auto SSS(float a, float b, float c) -> Types::VertexAttribute
		{
			if (!Helpers::ValidTriangle(a, b, c))
				return {};

			glm::vec3 v0(0.f, 0.f, 0.f);
			glm::vec3 v1(c, 0.f, 0.f);

			float x = (std::pow(a, 2.f) - std::pow(b, 2.f) + std::pow(c, 2.f) / (2.f * c));
			float y = std::sqrt(std::pow(a, 2.f) - std::pow((std::pow(a, 2.f) - std::pow(b, 2.f) + std::pow(c, 2.f)) / (2.f * c), 2.f));
			glm::vec3 v2(x, y, 0.f);

			Helpers::CenterTriangle(v0, v1, v2);

			return std::vector<glm::vec3>{ v0, v1, v2 };
		}

	}

}
