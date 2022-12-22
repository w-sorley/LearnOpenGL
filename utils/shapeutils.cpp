#include "shapeutils.h"


Shader* ShapeUtils::m_objectShader;
unsigned int ShapeUtils::cubeVAO;
unsigned int ShapeUtils::cubeTexture;

Shader* ShapeUtils::m_skyShader;
unsigned int ShapeUtils::skyVAO;
unsigned int ShapeUtils::skyTexture;
int ShapeUtils::init(){
    glEnable(GL_DEPTH_TEST); // 开启深度测试

    glEnable(GL_PROGRAM_POINT_SIZE); // 开启修改点图元的大小

   float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(3 * sizeof(float)));
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
    m_objectShader->setInt("skybox", 0);
    m_skyShader->use();
    m_skyShader->setInt("skybox", 0);

    unsigned int blockIndex = glGetUniformBlockIndex(m_objectShader->ID, "Matrices");
    glUniformBlockBinding(m_objectShader->ID, blockIndex, 0);  // 绑定到绑定点0，与ubo的绑定一致才能获得填充数据

    unsigned int ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW); // 分配数据
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4)); // 将指定范围绑定到绑定点0
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glm::mat4 projection = glm::perspective(glm::radians(100.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 填充数据
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glm::mat4 view = glm::mat4(1.0f);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return 0;
}

int ShapeUtils::Draw(){
    
    glm::mat4 model = glm::mat4(1.0f);

    // cubes
     m_objectShader->use();
    glUniform3f(glGetUniformLocation(m_objectShader->ID, "cameraPos"), 0.0f, 0.0f, 0.0f);
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, skyTexture); 	
    model = glm::translate(model, glm::vec3(-1.5f, 0.0f, -2.0f));
    m_objectShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // glDepthMask(GL_FALSE);  // 禁止写入深度信息，保证之后绘制的所有物体都不会被天空盒遮挡
    // glDepthFunc(GL_LEQUAL); //  小于等于1均通过
    // glBindVertexArray(skyVAO);
    // m_skyShader->use();
    // view = glm::mat4(1.0f);
    // m_skyShader->setMat4("view", view);
    // m_skyShader->setMat4("projection", projection);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // // glDepthMask(GL_TRUE);
    //  glDepthFunc(GL_LESS); 



    return 0;
}