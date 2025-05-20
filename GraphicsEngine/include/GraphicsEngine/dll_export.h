// Copyright (c) 2025 Milton McDonald (miltonmcdonald1986@gmail.com)
//
// This software is licensed under the MIT License.
// See LICENSE file for details.
//
// dll_export.h - Defines the DLLEXPORT macro for cross-platform compatibility.
// It ensures proper symbol exporting/importing for Windows while handling
// other platforms gracefully.

#ifndef GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_DLLIMPEXP_H_
#define GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_DLLIMPEXP_H_

#ifdef _WIN32
#ifdef GRAPHICSENGINE_EXPORTS
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllimport)
#endif
#elif defined(__linux__)
#define DLLEXPORT
#else
#define DLLEXPORT
#endif

#endif  // GRAPHICSENGINE_INCLUDE_GRAPHICSENGINE_DLLIMPEXP_H_
