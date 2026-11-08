#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

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

    void Draw(Shader shader)
    {
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;

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

        // Color del material (.mtl)
        glUniform3fv(
            glGetUniformLocation(shader.Program, "materialColor"),
            1,
            glm::value_ptr(this->materialColor)
        );

        // Bandera: 1 si tiene textura, 0 si usa solo color del .mtl
        glUniform1i(
            glGetUniformLocation(shader.Program, "hasTexture"),
            this->textures.size() > 0 ? 1 : 0
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