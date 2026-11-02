#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using namespace std;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint id;
    string type;
    aiString path;
};

class Mesh
{
public:
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    glm::vec3 materialColor;

    Mesh(vector<Vertex> vertices,
        vector<GLuint> indices,
        vector<Texture> textures,
        glm::vec3 materialColor)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        this->materialColor = materialColor;

        this->setupMesh();
    }

    void Draw(Shader shader, GLuint diffuseOverride = 0)
    {
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        bool hasSpecular = false;

        for (GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            stringstream ss;
            string number;
            string name = this->textures[i].type;

            if (name == "texture_diffuse")
            {
                ss << diffuseNr++;
            }
            else if (name == "texture_specular")
            {
                hasSpecular = true;
                ss << specularNr++;
            }

            number = ss.str();

            glUniform1i(
                glGetUniformLocation(
                    shader.Program,
                    (name + number).c_str()
                ),
                i
            );

            glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
        }

        // Una textura existente puede sustituir el pasto del piso sin editar el OBJ/MTL.
        if (diffuseOverride != 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseOverride);
            glUniform1i(glGetUniformLocation(shader.Program, "texture_diffuse1"), 0);
        }

        // Los MTL existentes documentan Kd > 1 como material luminoso.
        // Solo ese material emite: no se agrega una luz por cada vela decorativa.
        const float peak = (std::max)(materialColor.r, (std::max)(materialColor.g, materialColor.b));
        const glm::vec3 emission = peak > 1.0f ? materialColor * 0.7f : glm::vec3(0.0f);
        glUniform3fv(glGetUniformLocation(shader.Program, "emissionColor"), 1, glm::value_ptr(emission));
        glUniform1i(glGetUniformLocation(shader.Program, "hasSpecularTexture"), hasSpecular && diffuseOverride == 0 ? 1 : 0);

        // Color del material (.mtl)
        glUniform3fv(
            glGetUniformLocation(shader.Program, "materialColor"),
            1,
            glm::value_ptr(this->materialColor)
        );

        // Bandera: 1 si tiene textura, 0 si usa solo color del .mtl
        glUniform1i(
            glGetUniformLocation(shader.Program, "hasTexture"),
            (diffuseOverride != 0 || this->textures.size() > 0) ? 1 : 0
        );

        glUniform1f(
            glGetUniformLocation(shader.Program, "material.shininess"),
            16.0f
        );

        glBindVertexArray(this->VAO);

        glDrawElements(
            GL_TRIANGLES,
            this->indices.size(),
            GL_UNSIGNED_INT,
            0
        );

        glBindVertexArray(0);

        for (GLuint i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

private:
    GLuint VAO, VBO, EBO;

    void setupMesh()
    {
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(
            GL_ARRAY_BUFFER,
            this->vertices.size() * sizeof(Vertex),
            &this->vertices[0],
            GL_STATIC_DRAW
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            this->indices.size() * sizeof(GLuint),
            &this->indices[0],
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid*)0
        );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, Normal)
        );

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, TexCoords)
        );

        glBindVertexArray(0);
    }
};
