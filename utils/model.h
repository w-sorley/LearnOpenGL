#ifndef MODEL_H
#define MODEL_H

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include<vector>
#include<string>

#include "shader.h"
#include "mesh.h"

class Model {
public:
    Model(char *path);
    void Draw(Shader &shader);
private:
    vector<Mesh> meshes;
    string directory;
    vector<Texture> textures_loaded;
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTexures(aiMaterial *material, aiTextureType type, string typeName);
};


#endif