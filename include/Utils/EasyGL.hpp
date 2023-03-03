/*
 * @Author: ccysam
 * @E-Mail: ccysam@hotmail.com
 * @Date: 2022-11-25 19:41:07
 * @LastEditTime: 2023-01-11 16:56:06
 * @Description:
 * @Copyright: Copyright (c) 2022 by ccysam, All Rights Reserved.
 */
#pragma once
#ifndef __GL_SIMPLIFIED__
#define __GL_SIMPLIFIED__

// Includes

#include <vector>
#include <cstdarg>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

// Marcos

#define __PI (3.14159265358979323846)

#define GS_UINT unsigned int
#define GS_FLOAT float
#define GS_DOUBLE double
#define GS_DATA unsigned char *

// Declarations

// Language basic definitions to GL basic definitions

typedef GS_UINT glObjects;
typedef GS_UINT glShader;
typedef GS_UINT glVertex;
typedef GS_DATA glResource;
typedef GS_FLOAT glValue;

// GL basic definitions to GL definitions

typedef glObjects glVAO;
typedef glObjects glVBO;
typedef glObjects glEBO;
typedef glObjects glShaderProgram;
typedef glObjects glTexture;
typedef glResource glTexturePic;
typedef glShader VertexShader;
typedef glShader FragmentShader;

// Attributes of GL2D Shapes

namespace
{
    // const char *readAllLine(const char *filename)
    // {
    //     std::ifstream file;
    //     file.open(filename, std::ios::in);
    //     if (!file)
    //     {
    //         throw std::runtime_error("Failed to open file ");
    //     }
    //     return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()).c_str();
    // }
    const char *readVSH(const char *filename)
    {
        FILE *vsh;
        int file_size;
        char *tmp;
        vsh = fopen(filename, "r");
        fseek(vsh, 0, SEEK_END);
        file_size = ftell(vsh);
        tmp = (char *)malloc(file_size * sizeof(char));
        memset(tmp, '\0', file_size * sizeof(char));
        fseek(vsh, 0, SEEK_SET);
        fread(tmp, sizeof(char), file_size, vsh);
        fclose(vsh);
        const char *r = tmp;
        return r;
    }

    const char *readFSH(const char *filename)
    {
        FILE *fsh;
        int file_size;
        char *tmp;
        fsh = fopen(filename, "r");
        fseek(fsh, 0, SEEK_END);
        file_size = ftell(fsh);
        tmp = (char *)malloc(file_size * sizeof(char));
        memset(tmp, '\0', file_size * sizeof(char));
        fseek(fsh, 0, SEEK_SET);
        fread(tmp, sizeof(char), file_size, fsh);
        const char *r = tmp;
        fclose(fsh);
        return r;
    }
} // namespace

namespace EasyGL
{

    // Structures of simple objects

    typedef struct RGB
    {
        int red = 0;
        int green = 0;
        int blue = 0;

        RGB() {}

        RGB(int red, int green, int blue)
        {
            this->red = red;
            this->green = green;
            this->blue = blue;
        }

    } RGB;

    // Structures of complex objects

    typedef struct Shader
    {
        // Variables

        VertexShader vertexShader;
        FragmentShader fragmentShader;
        std::vector<glShader> externShaders;
        glShaderProgram shaderProgram;

        // Constructors and Destructor

        Shader()
        {
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        }

        Shader(const char *vsh, const char *fsh)
        {
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            SetVertexShaderFile(vsh);
            SetFragmentShaderFile(fsh);
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
        }

        Shader(VertexShader vs, FragmentShader fs, glShader es...)
        {
            vertexShader = vs;
            fragmentShader = fs;
            va_list vaList;
            va_start(vaList, es);
            externShaders.push_back(va_arg(vaList, glShader));
            va_end(vaList);
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            for (glShader s : externShaders)
            {
                glAttachShader(shaderProgram, s);
            }
        }

        Shader(glShaderProgram sPram)
        {
            shaderProgram = sPram;
            glLinkProgram(shaderProgram);
        }

        ~Shader()
        {
            // glDeleteShader(vertexShader);
            // glDeleteShader(fragmentShader);
            // if (!externShaders.empty())
            // {
            //     for (glShader s : externShaders)
            //     {
            //         glDeleteShader(s);
            //     }
            // }
            // glDeleteProgram(shaderProgram);
        }

        // Setters with complex operations

        /**
         * Set vertex shader from shader file (*.vsh is recommended)
         * @param {char} *filename VertexShader File full name (with path)
         */
        void SetVertexShaderFile(const char *filename)
        {
            // cFU::File file = cFU::File(filename);
            // const char *vsh = file.readAllLine();
            const char *vsh = readVSH(filename);
            glShaderSource(vertexShader, 1, &vsh, NULL);
            glCompileShader(vertexShader);
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                          << infoLog << std::endl;
            }
        }
        void SetVertexShader(const char *vsh)
        {
            glShaderSource(vertexShader, 1, &vsh, NULL);
            glCompileShader(vertexShader);
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                          << infoLog << std::endl;
            }
        }

        // Set fragment shader from shader file (*.fsh is recommended)
        /**
         * Set fragment shader from shader file (*.fsh is recommended)
         * @param {char} *filename FragmentShader File full name (with path)
         */
        void SetFragmentShaderFile(const char *filename)
        {
            // cFU::File file = cFU::File(filename);
            // const char *fsh = file.readAllLine();
            const char *fsh = readFSH(filename);
            glShaderSource(fragmentShader, 1, &fsh, NULL);
            glCompileShader(fragmentShader);
            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                          << infoLog << std::endl;
            }
        }
        void SetFragmentShader(const char *fsh)
        {
            glShaderSource(fragmentShader, 1, &fsh, NULL);
            glCompileShader(fragmentShader);
            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                          << infoLog << std::endl;
            }
        }

        // Finish all the works on shader compilation and return the final shaderProgram
        glShaderProgram create()
        {
            return shaderProgram;
        }
    } Shader;

    typedef struct Texture
    {
        int width, height, nrChannels;
        glTexturePic Pic;
        glTexture texture;

        Texture() {}

        Texture(const char *filename, GLint filter = GL_LINEAR, GLint warp = GL_REPEAT)
        {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warp);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
            stbi_set_flip_vertically_on_load(true);
            Pic = stbi_load(filename, &width, &height, &nrChannels, 0);
            if (Pic)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, Pic);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                throw std::runtime_error("Failed to load texture!");
            }
            stbi_image_free(Pic);
        }

        ~Texture()
        {
            // glDeleteTextures(1, &texture);
        }

        void setTexture(EasyGL::Texture texture)
        {
        }

        glTexture create()
        {
            return texture;
        }
    } Texture;

    typedef struct TextureA
    {
        int width, height, nrChannels;
        glTexturePic Pic;
        glTexture texture;

        TextureA() {}

        TextureA(const char *filename, GLint filter = GL_LINEAR, GLint warp = GL_REPEAT)
        {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warp);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
            stbi_set_flip_vertically_on_load(true);
            Pic = stbi_load(filename, &width, &height, &nrChannels, 0);
            if (Pic)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Pic);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                throw std::runtime_error("Failed to load texture!");
            }
            stbi_image_free(Pic);
        }

        ~TextureA()
        {
            // glDeleteTextures(1, &texture);
        }

        void setTexture(EasyGL::Texture texture)
        {
        }

        glTexture create()
        {
            return texture;
        }
    } TextureA;

    // Some utility functions

    inline RGB Hex2RGB(const char *colorHex)
    {
        int hex = std::strtol(colorHex, NULL, 16);
        int r = (hex >> 16) & 0xFF;
        int g = (hex >> 8) & 0xFF;
        int b = hex & 0xFF;
        return RGB(r, g, b);
    }
}
// Structures of 2D shapes

namespace EasyGL2D
{
    typedef struct Triangle
    {
        // Variables
        float vertices[9] = {0};
        glVAO vao;
        glVBO vbo;
        EasyGL::Shader shader;
        glShaderProgram shaderProgram;
        bool idTextured = false;
        EasyGL::RGB Color;

        // Constructor and Destructor

        Triangle() {}

        Triangle(float (&ary)[9])
        {
            for (int i = 0; i < 9; i++)
            {
                vertices[i] = ary[i];
            }
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GS_FLOAT), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
        {
            // Mapping vertices from param
            vertices[2] = vertices[5] = vertices[8] = 0.0f;
            vertices[0] = x1;
            vertices[1] = y1;
            vertices[3] = x2;
            vertices[4] = y2;
            vertices[6] = x3;
            vertices[7] = y3;
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GS_FLOAT), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        ~Triangle()
        {
            // glDeleteVertexArrays(1, &vao);
            // glDeleteBuffers(1, &vbo);
        }

        void setColor(const char *colorHex)
        {
            Color = EasyGL::Hex2RGB(colorHex);
        }

        void draw(glShaderProgram shader)
        {
            shaderProgram = shader;
            GLint colorLocation = glGetUniformLocation(shaderProgram, "targetColor");
            GLint isTLocation = glGetUniformLocation(shaderProgram, "isTexture");
            glUseProgram(shaderProgram);
            glUniform4f(colorLocation, ((float)Color.red) / 255.0, ((float)Color.green) / 255.0, ((float)Color.blue / 255.0), 1.0f);
            glUniform1i(isTLocation, GL_FALSE);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            // glDrawArrays
        }
    } Triangle;

    typedef struct Rectangle
    {
        float vertices[12] = {0.0f};
        glVAO vao;
        glVBO vbo;
        glEBO ebo;
        EasyGL::Shader shader;
        glShaderProgram shaderProgram;
        bool isTextured = false;
        EasyGL::RGB Color;
        glValue Transparency = 1.0f;

        Rectangle() {}

        Rectangle(float x, float y, float width, float height)
        {
            vertices[0] = x;
            vertices[1] = y;
            vertices[3] = x + width;
            vertices[4] = y;
            vertices[6] = x;
            vertices[7] = y + height;
            vertices[9] = x + width;
            vertices[10] = y + height;
            glVertex indices[] = {
                0, 1, 2,
                1, 2, 3};
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        ~Rectangle()
        {
            // glDeleteVertexArrays(1, &vao);
            // glDeleteBuffers(1, &vbo);
            // glDeleteBuffers(1, &ebo);
        }

        void setColor(const char *colorHex)
        {
            Color = EasyGL::Hex2RGB(colorHex);
        }

        void setTransparency(glValue transparency)
        {
            Transparency = transparency;
        }

        void draw(glShaderProgram shader)
        {
            shaderProgram = shader;
            GLint colorLocation = glGetUniformLocation(shaderProgram, "targetColor");
            GLint isTLocation = glGetUniformLocation(shaderProgram, "isTexture");
            glUseProgram(shaderProgram);
            glUniform4f(colorLocation, ((float)Color.red) / 255.0, ((float)Color.green) / 255.0, ((float)Color.blue / 255.0), Transparency);
            glUniform1i(isTLocation, GL_FALSE);
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    } Rectangle;

    typedef struct Line
    {
        // Variables
        float vertices[4] = {0};
        glVAO vao;
        glVBO vbo;
        EasyGL::Shader shader;
        glShaderProgram shaderProgram;
        float LineWidth;
        EasyGL::RGB Color;

        // Constructor and Destructor

        Line() {}

        Line(float x1, float y1, float x2, float y2, float width)
        {
            vertices[0] = x1;
            vertices[1] = y1;
            vertices[2] = x2;
            vertices[3] = y2;
            LineWidth = width;
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        ~Line()
        {
            // glDeleteVertexArrays(1, &vao);
            // glDeleteBuffers(1, &vbo);
        }

        void setColor(const char *colorHex)
        {
            Color = EasyGL::Hex2RGB(colorHex);
        }

        void draw(glShaderProgram shader)
        {
            shaderProgram = shader;
            GLint colorLocation = glGetUniformLocation(shaderProgram, "targetColor");
            GLint isTLocation = glGetUniformLocation(shaderProgram, "isTexture");
            glUseProgram(shaderProgram);
            glUniform4f(colorLocation, ((float)Color.red) / 255.0, ((float)Color.green) / 255.0, ((float)Color.blue / 255.0), 1.0f);
            glUniform1i(isTLocation, GL_FALSE);
            glBindVertexArray(vao);
            glLineWidth(LineWidth);
            glDrawArrays(GL_LINES, 0, 2);
        }
    } Line;

    typedef struct Disc
    {
        // Variables
        float vertices[360] = {0};
        int vertexCount = 360;
        glVAO vao;
        glVBO vbo;
        glShaderProgram shaderProgram;
        EasyGL::RGB Color;

        Disc() {}

        Disc(float x, float y, float radius)
        {
            for (int i = 0; i < vertexCount; i += 2)
            {
                vertices[i] = x + radius * cos(i * __PI / 180);
                vertices[i + 1] = y + radius * sin(i * __PI / 180);
            }
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        ~Disc()
        {
            // glDeleteVertexArrays(1, &vao);
            // glDeleteBuffers(1, &vbo);
        }

        void setColor(const char *colorHex)
        {
            Color = EasyGL::Hex2RGB(colorHex);
        }

        void draw(glShaderProgram shader)
        {

            shaderProgram = shader;
            GLint colorLocation = glGetUniformLocation(shaderProgram, "targetColor");
            GLint isTLocation = glGetUniformLocation(shaderProgram, "isTexture");
            glUseProgram(shaderProgram);
            glUniform4f(colorLocation, ((float)Color.red) / 255.0, ((float)Color.green) / 255.0, ((float)Color.blue / 255.0), 1.0f);
            glUniform1i(isTLocation, GL_FALSE);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 180);
            // glDrawArrays
        }

    } Disc;

    typedef struct Ring
    {
        // Variables
        float vertices[360] = {0};
        glVAO vao;
        glVBO vbo;
        glShaderProgram shaderProgram;
        EasyGL::RGB Color;
        int LineWidth;

        Ring() {}

        Ring(float x, float y, float radius, int lineWidth)
        {
            for (int i = 0; i < 360; i += 2)
            {
                vertices[i] = x + radius * cos(i * __PI / 180);
                vertices[i + 1] = y + radius * sin(i * __PI / 180);
            }
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 360 * sizeof(GL_FLOAT), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        ~Ring()
        {
            // glDeleteVertexArrays(1, &vao);
            // glDeleteBuffers(1, &vbo);
        }

        void setColor(const char *colorHex)
        {
            Color = EasyGL::Hex2RGB(colorHex);
        }

        void draw(glShaderProgram shader)
        {

            shaderProgram = shader;
            GLint colorLocation = glGetUniformLocation(shaderProgram, "targetColor");
            GLint isTLocation = glGetUniformLocation(shaderProgram, "isTexture");
            glUseProgram(shaderProgram);
            glUniform4f(colorLocation, ((float)Color.red) / 255.0, ((float)Color.green) / 255.0, ((float)Color.blue / 255.0), 1.0f);
            glUniform1i(isTLocation, GL_FALSE);
            glBindVertexArray(vao);
            glLineWidth(LineWidth);
            glDrawArrays(GL_LINE_LOOP, 0, 1);
        }

    } Ring;

    typedef struct PicCard
    {
        float vertices[20] = {0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                              0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                              0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
        glVAO vao;
        glVBO vbo;
        glEBO ebo;
        EasyGL::Shader shader;
        glShaderProgram shaderProgram;
        glTexture Texture;
        EasyGL::RGB Color;

        PicCard() {}

        PicCard(float x, float y, float width, float height)
        {
            vertices[0] = x;
            vertices[1] = y;
            vertices[5] = x + width;
            vertices[6] = y;
            vertices[10] = x;
            vertices[11] = y + height;
            vertices[15] = x + width;
            vertices[16] = y + height;
            glVertex indices[] = {
                0, 1, 2,
                1, 2, 3};
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        ~PicCard()
        {
            // glDeleteVertexArrays(1, &vao);
            // glDeleteBuffers(1, &vbo);
            // glDeleteBuffers(1, &ebo);
        }

        void setTexture(glTexture texture)
        {
            Texture = texture;
        }

        void draw(glShaderProgram shader)
        {
            shaderProgram = shader;
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            GLint colorLocation = glGetUniformLocation(shaderProgram, "targetColor");
            GLint isTLocation = glGetUniformLocation(shaderProgram, "isTexture");
            glBindTexture(GL_TEXTURE_2D, Texture);
            glUseProgram(shaderProgram);
            glUniform4f(colorLocation, ((float)Color.red) / 255.0, ((float)Color.green) / 255.0, ((float)Color.blue / 255.0), 1.0f);
            glUniform1i(isTLocation, GL_TRUE);
            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

    } PicCard;
}

#endif