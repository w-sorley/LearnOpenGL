#include "shapeutils.h"


Shader* ShapeUtils::m_objectShader;
unsigned int ShapeUtils::cubeVAO;
unsigned int ShapeUtils::cubeTexture;

Shader* ShapeUtils::m_skyShader;
unsigned int ShapeUtils::skyVAO;
unsigned int ShapeUtils::skyTexture;
int ShapeUtils::init(){
    glEnable(GL_DEPTH_TEST); // 开启深度测试

   float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};
    float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    } ;


    unsigned int cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int skyVBO;
    glGenBuffers(1, &skyVBO);
    glGenVertexArrays(1, &skyVAO);
    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    m_objectShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/depthTesting.vs", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/depthTesting.fs");
    cubeTexture  = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/marble.jpg");

    m_skyShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/skybox.vs", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/skybox.fs");
    vector<std::string> faces
    {
        "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/skybox/right.jpg",
        "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/skybox/left.jpg",
        "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/skybox/top.jpg",
        "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/skybox/bottom.jpg",
        "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/skybox/front.jpg",
        "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/skybox/back.jpg"
    };    
    skyTexture  = GLUtils::createCubeTexture(faces);


    m_objectShader->use();
    m_objectShader->setInt("texture1", 0);
    m_skyShader->use();
    m_skyShader->setInt("skybox", 0);

    return 0;
}

int ShapeUtils::Draw(){
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    // view = glm::translate(view, glm::vec3(-0.4f, 0.0f, -3.0f));  
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f)); 
    glm::mat4 projection = glm::perspective(glm::radians(100.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // cubes
     m_objectShader->use();
    m_objectShader->setMat4("view", view);
    m_objectShader->setMat4("projection", projection);
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cubeTexture); 	
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -2.4f));
    m_objectShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // glDepthMask(GL_FALSE);  // 禁止写入深度信息，保证之后绘制的所有物体都不会被天空盒遮挡
    glDepthFunc(GL_LEQUAL); //  小于等于1均通过
    glBindVertexArray(skyVAO);
    m_skyShader->use();
    view = glm::mat4(1.0f);
    m_skyShader->setMat4("view", view);
    m_skyShader->setMat4("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDepthMask(GL_TRUE);
     glDepthFunc(GL_LESS); 



    return 0;
}