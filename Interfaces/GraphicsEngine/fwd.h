#pragma once

typedef char GLchar;

typedef int GLint;
typedef int GLsizei;

typedef unsigned int GLenum;
typedef unsigned int GLuint;

#if defined(_WIN64)
typedef signed   long long int khronos_ssize_t;
#else
typedef signed   long  int     khronos_ssize_t;
#endif

typedef          float         khronos_float_t;
typedef khronos_float_t GLfloat;
typedef khronos_ssize_t GLsizeiptr;
