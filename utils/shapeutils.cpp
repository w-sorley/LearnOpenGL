#include "shapeutils.h"


Shader* ShapeUtils::m_objectShader;
Model* ShapeUtils::m_model;
int ShapeUtils::init(){
    glEnable(GL_DEPTH_TEST); // 开启深度测试

    m_objectShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/vertex.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/fragment.shader");
    m_model = new Model("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/nanosuit/nanosuit.obj");
    return 0;
}

int ShapeUtils::Draw(){
    m_objectShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -2.0f, -3.0f));
    m_objectShader->setMat4("projection", projection);
    m_objectShader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.5f));	// it's a bit too big for our scene, so scale it down
    model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_objectShader->setMat4("model", model);
    m_model->Draw(*m_objectShader);

    return 0;
}