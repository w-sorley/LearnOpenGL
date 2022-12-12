#include<mesh.h>

Mesh::Mesh(vector<Vertex> vertices, vector<Texture> textures, vector<unsigned int> indices) 
{
    this->vertices = vertices;
    this->textures = textures;
    this->indices = indices;

    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    

    // 必须在bindVBO配置顶点数据之前先bindVAO，VBO从属于VAO生效，VAO是绘制数据源的唯一标识
    glBindVertexArray(VAO);

    // 顶点数据（数据，索引，属性）
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader) {
    // 绑定纹理
    unsigned int diffuseNum = 1;
    unsigned int specularNum = 1;
    unsigned int normalNum = 1;
    unsigned int heightNum = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        string type = textures[i].type;
        string sampleIndex;
        if(type == "texture_difffuse") {
            sampleIndex = std::to_string(diffuseNum++);
        } else if(type == "texture_specular") {
            sampleIndex = std::to_string(specularNum++);
        } else if(type == "texture_normal") {
            sampleIndex = std::to_string(normalNum++); 
        } else if (type == "texture_height") {
            sampleIndex = std::to_string(heightNum++);
        } else {
            std::cout << "WARN: UNKNOWN TEXTURE TYPE:" << type << "!" << std::endl;
        }
        std::cout << "name = " << (type + sampleIndex) << std::endl;
        shader.setInt((type + sampleIndex).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].ID);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

    // 将设置回退到初始状态
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}