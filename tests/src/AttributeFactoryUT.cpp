#include <gtest/gtest.h>

#include <numbers>

#include "GraphicsEngine/AttributeFactory.h"

namespace g = ::graphics_engine;
namespace ga = g::attributes;
namespace gaa = g::attributes::attribute_factory;
namespace gaac = gaa::cube;
namespace gaat = gaa::triangle;

constexpr float kPi = std::numbers::pi_v<float>;
constexpr float kPiOver2 = kPi / 2.f;
constexpr float kDegsToRads = kPi / 180.f;

TEST(AttributeFactoryTests, Cube_Position) {
  ga::Attribute attribute = gaac::Position();
  EXPECT_TRUE(std::holds_alternative<std::vector<glm::vec3>>(attribute));

  auto v0 = glm::vec3(-0.5f, -0.5f, 0.5f);
  auto v1 = glm::vec3(0.5f, -0.5f, 0.5f);
  auto v2 = glm::vec3(0.5f, 0.5f, 0.5f);
  auto v3 = glm::vec3(-0.5f, 0.5f, 0.5f);
  auto v4 = glm::vec3(0.5f, -0.5f, -0.5f);
  auto v5 = glm::vec3(0.5f, 0.5f, -0.5f);
  auto v6 = glm::vec3(-0.5f, -0.5f, -0.5f);
  auto v7 = glm::vec3(-0.5f, 0.5f, -0.5f);

  auto pts = std::get<std::vector<glm::vec3>>(attribute);
  EXPECT_EQ(pts[0], v0);
  EXPECT_EQ(pts[1], v1);
  EXPECT_EQ(pts[2], v2);
  EXPECT_EQ(pts[3], v3);
  EXPECT_EQ(pts[4], v1);
  EXPECT_EQ(pts[5], v4);
  EXPECT_EQ(pts[6], v5);
  EXPECT_EQ(pts[7], v2);
  EXPECT_EQ(pts[8], v4);
  EXPECT_EQ(pts[9], v6);
  EXPECT_EQ(pts[10], v7);
  EXPECT_EQ(pts[11], v5);
  EXPECT_EQ(pts[12], v6);
  EXPECT_EQ(pts[13], v0);
  EXPECT_EQ(pts[14], v3);
  EXPECT_EQ(pts[15], v7);
  EXPECT_EQ(pts[16], v6);
  EXPECT_EQ(pts[17], v4);
  EXPECT_EQ(pts[18], v1);
  EXPECT_EQ(pts[19], v0);
  EXPECT_EQ(pts[20], v3);
  EXPECT_EQ(pts[21], v2);
  EXPECT_EQ(pts[22], v5);
  EXPECT_EQ(pts[23], v7);
}

TEST(AttributeFactoryTests, Cube_TextureCoordinates) {
  ga::Attribute attribute = gaac::TextureCoordinates();
  EXPECT_TRUE(std::holds_alternative<std::vector<glm::vec2>>(attribute));

  auto t0 = glm::vec2(0.f, 0.f);
  auto t1 = glm::vec2(1.f, 0.f);
  auto t2 = glm::vec2(1.f, 1.f);
  auto t3 = glm::vec2(0.f, 1.f);

  auto pts = std::get<std::vector<glm::vec2>>(attribute);
  EXPECT_EQ(pts[0], t0);
  EXPECT_EQ(pts[1], t1);
  EXPECT_EQ(pts[2], t2);
  EXPECT_EQ(pts[3], t3);
  EXPECT_EQ(pts[4], t0);
  EXPECT_EQ(pts[5], t1);
  EXPECT_EQ(pts[6], t2);
  EXPECT_EQ(pts[7], t3);
  EXPECT_EQ(pts[8], t0);
  EXPECT_EQ(pts[9], t1);
  EXPECT_EQ(pts[10], t2);
  EXPECT_EQ(pts[11], t3);
  EXPECT_EQ(pts[12], t0);
  EXPECT_EQ(pts[13], t1);
  EXPECT_EQ(pts[14], t2);
  EXPECT_EQ(pts[15], t3);
  EXPECT_EQ(pts[16], t0);
  EXPECT_EQ(pts[17], t1);
  EXPECT_EQ(pts[18], t2);
  EXPECT_EQ(pts[19], t3);
  EXPECT_EQ(pts[20], t0);
  EXPECT_EQ(pts[21], t1);
  EXPECT_EQ(pts[22], t2);
  EXPECT_EQ(pts[23], t3);
}

TEST(AttributeFactoryTests, Triangle_AAS) {
  std::expected<ga::Attribute, g::Error> expectedAttribute =
      gaat::AAS(0.5f, 1.f, 3.f);
  EXPECT_TRUE(expectedAttribute.has_value());

  const auto& attribute = expectedAttribute.value();
  EXPECT_TRUE(std::holds_alternative<std::vector<glm::vec3>>(attribute));

  const auto& pts = std::get<std::vector<glm::vec3>>(attribute);
  EXPECT_TRUE(pts.size() == 3);
  EXPECT_EQ(pts[0].x, -3.62090683f);
  EXPECT_EQ(pts[0].y, -0.841470957f);
  EXPECT_EQ(pts[0].z, 0.f);
  EXPECT_EQ(pts[1].x, 2.62090683f);
  EXPECT_EQ(pts[1].y, -0.841470957f);
  EXPECT_EQ(pts[1].z, 0.f);
  EXPECT_EQ(pts[2].x, 1.f);
  EXPECT_EQ(pts[2].y, 1.68294191f);
  EXPECT_EQ(pts[2].z, 0.f);

  std::expected<ga::Attribute, g::Error> error_bad_angle_a =
      gaat::AAS(0.f, 1.f, 3.f);
  EXPECT_FALSE(error_bad_angle_a.has_value());
  EXPECT_EQ(error_bad_angle_a.error().code, g::ErrorCode::kInvalidAngle);

  std::expected<ga::Attribute, g::Error> error_bad_angle_b =
      gaat::AAS(0.5f, 0.f, 3.f);
  EXPECT_FALSE(error_bad_angle_b.has_value());
  EXPECT_EQ(error_bad_angle_b.error().code, g::ErrorCode::kInvalidAngle);

  std::expected<ga::Attribute, g::Error> error_bad_side_a =
      gaat::AAS(0.5f, 1.f, 0.f);
  EXPECT_FALSE(error_bad_side_a.has_value());
  EXPECT_EQ(error_bad_side_a.error().code, g::ErrorCode::kInvalidSideLength);

  std::expected<ga::Attribute, g::Error> error_bad_angles =
      gaat::AAS(kPiOver2, kPiOver2, 3.f);
  EXPECT_FALSE(error_bad_angles.has_value());
  EXPECT_EQ(error_bad_angles.error().code, g::ErrorCode::kAngleSumExceeded);
}

TEST(AttributeFactoryTests, Triangle_ASA) {
  auto angle_a = 40.f * kDegsToRads;
  auto side_c = 5.f;
  auto angle_b = 60.f * kDegsToRads;
  std::expected<ga::Attribute, g::Error> attr =
      gaat::ASA(angle_a, side_c, angle_b);

  EXPECT_TRUE(attr.has_value());
  EXPECT_TRUE(std::holds_alternative<std::vector<glm::vec3>>(attr.value()));

  const auto& pts = std::get<std::vector<glm::vec3>>(attr.value());
  EXPECT_TRUE(pts.size() == 3);
  EXPECT_EQ(pts[0].x, -2.78941369f);
  EXPECT_EQ(pts[0].y, -0.942096531f);
  EXPECT_EQ(pts[0].z, 0.f);
  EXPECT_EQ(pts[1].x, 2.21058631f);
  EXPECT_EQ(pts[1].y, -0.942096531f);
  EXPECT_EQ(pts[1].z, 0.f);
  EXPECT_EQ(pts[2].x, 0.578827381f);
  EXPECT_EQ(pts[2].y, 1.88419318f);
  EXPECT_EQ(pts[2].z, 0.f);

  std::expected<ga::Attribute, g::Error> error_bad_angle_a =
      gaat::ASA(-1.f, side_c, angle_b);
  EXPECT_FALSE(error_bad_angle_a.has_value());
  EXPECT_EQ(error_bad_angle_a.error().code, g::ErrorCode::kInvalidAngle);

  std::expected<ga::Attribute, g::Error> error_bad_side_c =
      gaat::ASA(angle_a, -1.f, angle_b);
  EXPECT_FALSE(error_bad_side_c.has_value());
  EXPECT_EQ(error_bad_side_c.error().code, g::ErrorCode::kInvalidSideLength);

  std::expected<ga::Attribute, g::Error> error_bad_angle_b =
      gaat::ASA(angle_a, side_c, -1.f);
  EXPECT_FALSE(error_bad_angle_b.has_value());
  EXPECT_EQ(error_bad_angle_b.error().code, g::ErrorCode::kInvalidAngle);
  
  std::expected<ga::Attribute, g::Error> error_bad_angles =
      gaat::ASA(kPiOver2, side_c, kPiOver2);
  EXPECT_FALSE(error_bad_angles.has_value());
  EXPECT_EQ(error_bad_angles.error().code, g::ErrorCode::kAngleSumExceeded);
}
