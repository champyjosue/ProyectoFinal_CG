#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"
#include "Shader.h"

class SkyBox
{
public:
    bool Load()
    {
        Shader shader("Shader/SkyBox.vs", "Shader/SkyBox.frag");
        program = shader.Program;
        GLint linked = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked) return Fail("programa GLSL sin enlazar");

        samplerLocation = glGetUniformLocation(program, "skybox");
        viewLocation = glGetUniformLocation(program, "view");
        projectionLocation = glGetUniformLocation(program, "projection");
        if (samplerLocation < 0 || viewLocation < 0 || projectionLocation < 0)
            return Fail("uniforms incompletos");

        if (!LoadFaces()) return Fail("no se pudo crear el cubemap completo");

        const GLfloat vertices[] = {
            -1, 1,-1, -1,-1,-1,  1,-1,-1,  1,-1,-1,  1, 1,-1, -1, 1,-1,
            -1,-1, 1, -1,-1,-1, -1, 1,-1, -1, 1,-1, -1, 1, 1, -1,-1, 1,
             1,-1,-1,  1,-1, 1,  1, 1, 1,  1, 1, 1,  1, 1,-1,  1,-1,-1,
            -1,-1, 1, -1, 1, 1,  1, 1, 1,  1, 1, 1,  1,-1, 1, -1,-1, 1,
            -1, 1,-1,  1, 1,-1,  1, 1, 1,  1, 1, 1, -1, 1, 1, -1, 1,-1,
            -1,-1,-1, -1,-1, 1,  1,-1,-1,  1,-1,-1, -1,-1, 1,  1,-1, 1
        };
        GLint previousVAO = 0, previousBuffer = 0, previousProgram = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVAO);
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &previousBuffer);
        glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
        glBindVertexArray(previousVAO);
        glBindBuffer(GL_ARRAY_BUFFER, previousBuffer);

        glUseProgram(program);
        glUniform1i(samplerLocation, textureUnit);
        glUseProgram(previousProgram);
        if (!vao || !vbo || glGetError() != GL_NO_ERROR)
            return Fail("no se pudo preparar la geometria del cielo");
        return true;
    }

    bool Draw(const glm::mat4& view, const glm::mat4& projection, bool verify) const
    {
        GLint previousProgram = 0, previousVAO = 0, previousDepth = 0;
        GLint previousUnit = 0, previousCube = 0;
        GLboolean previousMask = GL_TRUE;
        glGetIntegerv(GL_CURRENT_PROGRAM, &previousProgram);
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &previousVAO);
        glGetIntegerv(GL_DEPTH_FUNC, &previousDepth);
        glGetBooleanv(GL_DEPTH_WRITEMASK, &previousMask);
        glGetIntegerv(GL_ACTIVE_TEXTURE, &previousUnit);
        const bool seamless = glIsEnabled(GL_TEXTURE_CUBE_MAP_SEAMLESS) == GL_TRUE;

        // La vista del cielo conserva solo la rotacion de la camara.
        const glm::mat4 skyView{glm::mat3(view)};
        glUseProgram(program);
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(skyView));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);
        if (!seamless) glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &previousCube);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
        glBindVertexArray(vao);
        const bool valid = !verify || VerifyBinding();
        if (valid) glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(previousVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, previousCube);
        glActiveTexture(previousUnit);
        if (!seamless) glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glDepthMask(previousMask);
        glDepthFunc(previousDepth);
        glUseProgram(previousProgram);
        return valid;
    }

    void Release()
    {
        if (cubemap) glDeleteTextures(1, &cubemap);
        if (vao) glDeleteVertexArrays(1, &vao);
        if (vbo) glDeleteBuffers(1, &vbo);
        if (program) glDeleteProgram(program);
        cubemap = vao = vbo = program = 0;
    }

private:
    static constexpr GLint textureUnit = 1;
    GLuint cubemap = 0, vao = 0, vbo = 0, program = 0;
    GLint samplerLocation = -1, viewLocation = -1, projectionLocation = -1;
    int faceSize = 0;

    bool Fail(const char* reason)
    {
        std::cerr << "ERROR SKYBOX: " << reason << ". Use --skybox=off para el fondo anterior." << std::endl;
        Release();
        return false;
    }

    bool LoadFaces()
    {
        // Orden OpenGL: +X, -X, +Y, -Y, +Z, -Z.
        const std::array<const char*, 6> paths = {{
            "SkyBox/Alan/right.jpg", "SkyBox/Alan/left.jpg",
            "SkyBox/Alan/top.jpg", "SkyBox/Alan/bottom.jpg",
            "SkyBox/Alan/back.jpg", "SkyBox/Alan/front.jpg"
        }};
        GLint previousUnit = 0, previousCube = 0, previousAlignment = 0, maxSize = 0;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &previousUnit);
        glGetIntegerv(GL_UNPACK_ALIGNMENT, &previousAlignment);
        glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &maxSize);
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &previousCube);
        glGenTextures(1, &cubemap);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        bool valid = cubemap != 0;
        for (size_t face = 0; valid && face < paths.size(); ++face)
        {
            int width = 0, height = 0, channels = 0;
            const std::unique_ptr<unsigned char, decltype(&SOIL_free_image_data)> image(
                SOIL_load_image(paths[face], &width, &height, &channels, SOIL_LOAD_RGB), SOIL_free_image_data);
            if (!image || width <= 0 || width != height || width > maxSize || (face && width != faceSize))
            {
                std::cerr << "SKYBOX imagen invalida: " << paths[face] << " (" << width << "x" << height << ")" << std::endl;
                valid = false;
                break;
            }
            faceSize = width;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<GLenum>(face), 0, GL_RGB8,
                         width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.get());
            std::cout << "SKYBOX cara=" << face << " imagen=" << paths[face] << " size=" << width << "x" << height << std::endl;
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glPixelStorei(GL_UNPACK_ALIGNMENT, previousAlignment);
        glBindTexture(GL_TEXTURE_CUBE_MAP, previousCube);
        glActiveTexture(previousUnit);
        return valid && glGetError() == GL_NO_ERROR;
    }

    bool VerifyBinding() const
    {
        GLint sampler = -1, activeUnit = 0, binding = 0, activeProgram = 0;
        glGetUniformiv(program, samplerLocation, &sampler);
        glGetIntegerv(GL_ACTIVE_TEXTURE, &activeUnit);
        glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &binding);
        glGetIntegerv(GL_CURRENT_PROGRAM, &activeProgram);
        int completeFaces = 0;
        for (GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X; face <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; ++face)
        {
            GLint width = 0, height = 0, format = 0;
            glGetTexLevelParameteriv(face, 0, GL_TEXTURE_WIDTH, &width);
            glGetTexLevelParameteriv(face, 0, GL_TEXTURE_HEIGHT, &height);
            glGetTexLevelParameteriv(face, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
            if (width == faceSize && height == faceSize && format == GL_RGB8) ++completeFaces;
        }
        const bool valid = sampler == textureUnit && activeUnit == GL_TEXTURE0 + sampler &&
            static_cast<GLuint>(binding) == cubemap && glIsTexture(cubemap) &&
            static_cast<GLuint>(activeProgram) == program && completeFaces == 6;
        std::cout << "SKYBOX GPU: id_creado=" << cubemap << " id_muestreado=" << binding
                  << " sampler=" << sampler << " unidad_activa=" << activeUnit - GL_TEXTURE0
                  << " caras_RGB8=" << completeFaces << " size=" << faceSize << "x" << faceSize
                  << " valido=" << valid << std::endl;
        return valid;
    }
};
