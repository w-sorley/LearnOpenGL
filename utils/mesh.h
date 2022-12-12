#ifndef MESH_H
#define MESH_H

#include <glad.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/scene.h>

#include<vector>
#include<string>
using namespace std;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    GLuint ID;
    string type;
    aiString path;
};

class Mesh {
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;
    
    Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<unsigned int> indices);
    void Draw(Shader &shader);

private:
    unsigned int VBO, EBO;
    void setupMesh();
};


#endif