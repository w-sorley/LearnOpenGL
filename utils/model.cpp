#include"model.h"

Model::Model(char *path)
{
    loadModel(path);
}

void Model::Draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader);
    }
}

void Model::loadModel(string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR: ASSIMP LOAD MODEL FILE ERROR:" << import.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

// node中只是保存Mesh的索引值，所有的Mesh均统一保存在scene下（更节省空间）
void Model::processNode(aiNode *node, const aiScene *scene) 
{
    
    // 处理当前节点
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // 递归处理子点
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
    
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textues;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // 顶点信息
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        vertex.Position = vector;
         if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        
        if(mesh->mTextureCoords[0]) {
            glm::vec2 texCoord;
            texCoord.x = mesh->mTextureCoords[0][i].x;
            texCoord.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = texCoord;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // 索引信息
    for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    //材质纹理信息
    if(mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex]; 
        vector<Texture> diffuseTexures = loadMaterialTexures(material, aiTextureType_DIFFUSE, "texture_difffuse");
        textues.insert(textues.end(), diffuseTexures.begin(), diffuseTexures.end());
        vector<Texture> specularTexures = loadMaterialTexures(material, aiTextureType_SPECULAR, "texture_specular");
        textues.insert(textues.end(), specularTexures.begin(), specularTexures.end());
    }
    return Mesh(vertices, textues, indices);
}

vector<Texture> Model::loadMaterialTexures(aiMaterial *material, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        // 优化：避免重复加载
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++){
            if(std::strcmp(textures_loaded[j].path.data, str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip) {
            Texture texture;
            texture.ID = GLUtils::createTextureFromFile(str.C_Str(), directory.c_str());
            texture.path = str.C_Str();
            texture.type = typeName;
            textures.push_back(texture);
            textures_loaded.push_back(texture); // 添加到已加载的纹理中
        }
    }
    return textures;
}
