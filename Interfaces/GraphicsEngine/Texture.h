#pragma once

#include "GraphicsEngineImpExp.h"

namespace GraphicsEngine::Texture
{

    template <typename Key_t, typename Value_t>
    auto ReverseMap(const std::map<Key_t, Value_t>& originalMap) 
    {
        std::map<Value_t, Key_t> reversedMap;
        for (const auto& pair : originalMap) 
        {
            reversedMap.insert(pair.second, pair.first);
        }

        return reversedMap;
    }

    enum class MinifyingOption : int
    {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear
    };

    enum class MagnifyingOption : int
    {
        Nearest,
        Linear
    };

    const std::map<MinifyingOption, GLint> MinifyingOptionToGLint = {
        std::make_pair(MinifyingOption::Nearest, GL_NEAREST),
        std::make_pair(MinifyingOption::Linear, GL_LINEAR),
        std::make_pair(MinifyingOption::Linear, GL_LINEAR),
        std::make_pair(MinifyingOption::Linear, GL_LINEAR),
        std::make_pair(MinifyingOption::Linear, GL_LINEAR),
        std::make_pair(MinifyingOption::Linear, GL_LINEAR),
        };

    const std::map<MagnifyingOption, GLint> MagnifyingOptionToGLint = {
        std::make_pair(MagnifyingOption::Nearest, GL_NEAREST),
        std::make_pair(MagnifyingOption::Linear, GL_LINEAR)
    };

    enum class WrapOption : int
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    const std::map<WrapOption, GLint> WrapOptionToGLint = {
        std::make_pair(WrapOption::Repeat, GL_REPEAT),
        std::make_pair(WrapOption::MirroredRepeat, GL_MIRRORED_REPEAT),
        std::make_pair(WrapOption::ClampToEdge, GL_CLAMP_TO_EDGE),
        std::make_pair(WrapOption::ClampToBorder, GL_CLAMP_TO_BORDER)
        };

    GRAPHICSENGINE_API auto GenerateTexture2D(const std::filesystem::path& path, WrapOption wrapS, WrapOption wrapT, MinifyingOption filterMin, MagnifyingOption filterMag) -> std::optional<unsigned int>
    {
        static_assert(std::is_same<unsigned int, GLuint>::value, "GLuint is not unsigned int");

        GLuint texture;
        glGenTextures(1, &texture);
        if (GL_ERROR())
            return std::nullopt;

        glBindTexture(GL_TEXTURE_2D, texture);
        if (GL_ERROR())
            return std::nullopt;

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapOptionToGLint.at(wrapS));
        if (GL_ERROR())
            return std::nullopt;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapOptionToGLint.at(wrapT));
        if (GL_ERROR())
            return std::nullopt;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinifyingOptionToGLint.at(filterMin));
        if (GL_ERROR())
            return std::nullopt;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, MagnifyingOptionToGLint.at(filterMag));
        if (GL_ERROR())
            return std::nullopt;
        
        // load and generate the texture
        int width, height, nrChannels;
        unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &nrChannels, 0);
        
        bool success = false;
        if (data)
        {
            success = true;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            if (GL_ERROR())
                return std::nullopt;

            glGenerateMipmap(GL_TEXTURE_2D);
            if (GL_ERROR())
                return std::nullopt;
        }
        
        stbi_image_free(data);

        if (success)
            return static_cast<unsigned int>(texture);
        else
            return std::nullopt;
    }

}
