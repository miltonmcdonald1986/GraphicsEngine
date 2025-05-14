#include <gtest/gtest.h>

#include "GraphicsEngine/AttributeFactory.h"

using namespace GraphicsEngine;

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
