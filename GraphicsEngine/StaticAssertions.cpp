#pragma once

#include <type_traits>

#include "glad/glad.h"

static_assert(std::is_same<GLint, int>::value, "GLint is not the same as int");
static_assert(std::is_same<GLuint, unsigned int>::value, "GLuint is not the same as unsigned int");
