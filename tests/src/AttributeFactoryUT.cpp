#include <gtest/gtest.h>

#include "GraphicsEngine/AttributeFactory.h"

using namespace GraphicsEngine;

TEST (AttributeFactoryTests, Cube_Position)
{
	Types::VertexAttribute attribute = AttributeFactory::Cube::Position ();
	EXPECT_TRUE (std::holds_alternative<std::vector<glm::vec3>> (attribute));

	auto v0 = glm::vec3 (-0.5f, -0.5f, 0.5f);
	auto v1 = glm::vec3 (0.5f, -0.5f, 0.5f);
	auto v2 = glm::vec3 (0.5f, 0.5f, 0.5f);
	auto v3 = glm::vec3 (-0.5f, 0.5f, 0.5f);
	auto v4 = glm::vec3 (0.5f, -0.5f, -0.5f);
	auto v5 = glm::vec3 (0.5f, 0.5f, -0.5f);
	auto v6 = glm::vec3 (-0.5f, -0.5f, -0.5f);
	auto v7 = glm::vec3 (-0.5f, 0.5f, -0.5f);
	
	auto pts = std::get<std::vector<glm::vec3>> (attribute);
	EXPECT_EQ (pts[0],	v0);
	EXPECT_EQ (pts[1],	v1);
	EXPECT_EQ (pts[2],	v2);
	EXPECT_EQ (pts[3],	v3);
	EXPECT_EQ (pts[4],	v1);
	EXPECT_EQ (pts[5],	v4);
	EXPECT_EQ (pts[6],	v5);
	EXPECT_EQ (pts[7],	v2);
	EXPECT_EQ (pts[8],	v4);
	EXPECT_EQ (pts[9],	v6);
	EXPECT_EQ (pts[10], v7);
	EXPECT_EQ (pts[11], v5);
	EXPECT_EQ (pts[12], v6);
	EXPECT_EQ (pts[13], v0);
	EXPECT_EQ (pts[14], v3);
	EXPECT_EQ (pts[15], v7);
	EXPECT_EQ (pts[16], v6);
	EXPECT_EQ (pts[17], v4);
	EXPECT_EQ (pts[18], v1);
	EXPECT_EQ (pts[19], v0);
	EXPECT_EQ (pts[20], v3);
	EXPECT_EQ (pts[21], v2);
	EXPECT_EQ (pts[22], v5);
	EXPECT_EQ (pts[23], v7);
}

TEST (AttributeFactoryTests, Cube_TextureCoordinates) 
{
	Types::VertexAttribute attribute = AttributeFactory::Cube::TextureCoordinates ();
	EXPECT_TRUE(std::holds_alternative<std::vector<glm::vec2>> (attribute));
	
	auto t0 = glm::vec2 (0.f, 0.f);
	auto t1 = glm::vec2 (1.f, 0.f);
	auto t2 = glm::vec2 (1.f, 1.f);
	auto t3 = glm::vec2 (0.f, 1.f);

	auto pts = std::get<std::vector<glm::vec2>> (attribute);
	EXPECT_EQ (pts[0],	t0);
	EXPECT_EQ (pts[1],	t1);
	EXPECT_EQ (pts[2],	t2);
	EXPECT_EQ (pts[3],	t3);
	EXPECT_EQ (pts[4],	t0);
	EXPECT_EQ (pts[5],	t1);
	EXPECT_EQ (pts[6],	t2);
	EXPECT_EQ (pts[7],	t3);
	EXPECT_EQ (pts[8],	t0);
	EXPECT_EQ (pts[9],	t1);
	EXPECT_EQ (pts[10], t2);
	EXPECT_EQ (pts[11], t3);
	EXPECT_EQ (pts[12], t0);
	EXPECT_EQ (pts[13], t1);
	EXPECT_EQ (pts[14], t2);
	EXPECT_EQ (pts[15], t3);
	EXPECT_EQ (pts[16], t0);
	EXPECT_EQ (pts[17], t1);
	EXPECT_EQ (pts[18], t2);
	EXPECT_EQ (pts[19], t3);
	EXPECT_EQ (pts[20], t0);
	EXPECT_EQ (pts[21], t1);
	EXPECT_EQ (pts[22], t2);
	EXPECT_EQ (pts[23], t3);
}
