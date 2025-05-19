#include "AttributeFactory.h"

#include "attribute_factory_utilities.h"

namespace graphics_engine::attributes::attribute_factory {

namespace {

const std::string kErrMsgInvalidAngle =
    "Provided angle is less than or equal to zero.";

const std::string kErrMsgInvalidSideLength =
    "Provided side is less than or equal to zero.";

const std::string kErrMessageSumOfAnglesExceeded =
    "Sum of provided angles is greater than or equal to pi radians.";

}  // namespace

namespace cube {

Attribute TextureCoordinates() {
  // Each face has four texture coordinates, which we apply in counterclockwise
  // order.
  auto t0 = glm::vec2(0.f, 0.f);
  auto t1 = glm::vec2(1.f, 0.f);
  auto t2 = glm::vec2(1.f, 1.f);
  auto t3 = glm::vec2(0.f, 1.f);

  // Associate each face to the texture coordinates
  return std::vector<glm::vec2>{
      t0, t1, t2, t3,  // FACE 0
      t0, t1, t2, t3,  // FACE 1
      t0, t1, t2, t3,  // FACE 2
      t0, t1, t2, t3,  // FACE 3
      t0, t1, t2, t3,  // FACE 4
      t0, t1, t2, t3   // FACE 5
  };
}

Attribute Position() {
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
  return std::vector<glm::vec3>{
      v0, v1, v2, v3,  // FACE 0
      v1, v4, v5, v2,  // FACE 1
      v4, v6, v7, v5,  // FACE 2
      v6, v0, v3, v7,  // FACE 3
      v6, v4, v1, v0,  // FACE 4
      v3, v2, v5, v7   // FACE 5
  };
}

}  // namespace cube

namespace triangle {

std::expected<Attribute, Error> AAS(float angle_a, float angle_b,
                                    float side_a) {
  if (angle_a <= 0.f || angle_b <= 0.f)
    return std::unexpected(
        Error{ErrorCode::kInvalidAngle, kErrMsgInvalidAngle});

  if (side_a <= 0.f)
    return std::unexpected(
        Error{ErrorCode::kInvalidSideLength, kErrMsgInvalidSideLength});

  if (angle_a + angle_b >= std::numbers::pi_v<float>)
    return std::unexpected(
        Error{ErrorCode::kAngleSumExceeded, kErrMessageSumOfAnglesExceeded});

  glm::vec3 v0(0.f, 0.f, 0.f);

  const float side_b = side_a * std::sin(angle_b) / std::sin(angle_a);

  const float c0 = side_b * std::cos(angle_a);
  const float c1 = side_a * std::cos(angle_b);
  const float side_c = c0 + c1;

  glm::vec3 v1(side_c, 0.f, 0.f);
  glm::vec3 v2(c0, side_a * std::sin(angle_b), 0.f);

  if (std::expected<void, Error> result =
          utilities::center_triangle(v0, v1, v2);
      !result.has_value())
    return std::unexpected(result.error());

  return std::vector<glm::vec3>{v0, v1, v2};
}

std::expected<Attribute, Error> ASA(float angle_a, float side_c,
                                    float angle_b) {
  if (angle_a <= 0.f || angle_b <= 0.f)
    return std::unexpected(
        Error{ErrorCode::kInvalidAngle, kErrMsgInvalidAngle});

  if (side_c <= 0.f)
    return std::unexpected(
        Error{ErrorCode::kInvalidSideLength, kErrMsgInvalidSideLength});

  if (angle_a + angle_b >= std::numbers::pi_v<float>)
    return std::unexpected(
        Error{ErrorCode::kAngleSumExceeded, kErrMessageSumOfAnglesExceeded});

  glm::vec3 v0(0.f, 0.f, 0.f);
  glm::vec3 v1(side_c, 0.f, 0.f);

  const float angle_c = std::numbers::pi_v<float> - angle_a - angle_b;
  const float side_a = side_c * std::sin(angle_a) / std::sin(angle_c);
  const float x = side_c - side_a * std::cos(angle_b);
  const float y = side_a * std::sin(angle_b);
  glm::vec3 v2(x, y, 0.f);

  if (std::expected<void, Error> result =
          utilities::center_triangle(v0, v1, v2);
      !result.has_value())
    return std::unexpected(result.error());

  return std::vector<glm::vec3>{v0, v1, v2};
}

Attribute HL(float hypotenuse, float leg) {
  if (hypotenuse <= 0.f || leg <= 0.f) return {};

  if (hypotenuse <= leg) return {};

  glm::vec3 v0(0.f, 0.f, 0.f);
  glm::vec3 v1(leg, 0.f, 0.f);
  glm::vec3 v2(0.f, std::sqrt(std::pow(hypotenuse, 2.f) - std::pow(leg, 2.f)),
               0.f);

  utilities::center_triangle(v0, v1, v2);

  return std::vector<glm::vec3>{v0, v1, v2};
}

Attribute SAS(float a, float C, float b) {
  if (a <= 0.f || b <= 0.f) return {};

  if (C <= 0.f || C >= std::numbers::pi_v<float>) return {};

  glm::vec3 v0(0.f, 0.f, 0.f);
  glm::vec3 v1(a, 0.f, 0.f);

  float y = b * std::sin(C);
  float x = a - b * std::cos(C);
  glm::vec3 v2(x, y, 0.f);

  utilities::center_triangle(v0, v1, v2);

  return std::vector<glm::vec3>{v0, v1, v2};
}

Attribute SSS(float a, float b, float c) {
  if (!utilities::is_valid_triangle(a, b, c)) return {};

  glm::vec3 v0(0.f, 0.f, 0.f);
  glm::vec3 v1(c, 0.f, 0.f);

  float x =
      (std::pow(a, 2.f) - std::pow(b, 2.f) + std::pow(c, 2.f) / (2.f * c));
  float y = std::sqrt(
      std::pow(a, 2.f) -
      std::pow(
          (std::pow(a, 2.f) - std::pow(b, 2.f) + std::pow(c, 2.f)) / (2.f * c),
          2.f));
  glm::vec3 v2(x, y, 0.f);

  utilities::center_triangle(v0, v1, v2);

  return std::vector<glm::vec3>{v0, v1, v2};
}

}  // namespace triangle

}  // namespace graphics_engine::attributes::attribute_factory
