#include "shapeutils.h"


Shader* ShapeUtils::m_objectShader;
Model* ShapeUtils::m_model;
Model* ShapeUtils::m_rockModel;
glm::mat4* ShapeUtils::m_modelMatrices;
unsigned int ShapeUtils::m_amount = 300;
int ShapeUtils::init(){
    glEnable(GL_DEPTH_TEST); // 开启深度测试

    m_objectShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/vertex.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/fragment.shader");
    m_model = new Model("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/obj/planet/planet.obj");
    m_rockModel = new Model("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/obj/rock/rock.obj");

    m_modelMatrices = new glm::mat4[m_amount];
    srand(static_cast<unsigned int>(glfwGetTime())); // 
    float radius = 50;
    float offset = 2.5;
    for(unsigned int i = 0; i < m_amount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        float angle  = ((float)i / (float)m_amount) * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        float scale = static_cast<float>((rand() % 20)/ 100 + 0.05);
        model = glm::translate(model, glm::vec3(scale));

        float rotAngle = static_cast<float>(rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f)); //

        m_modelMatrices[i] = model; 
    }


    return 0;
}

int ShapeUtils::Draw(){
    m_objectShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)800 / (float)600, 0.1f, 1000.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -10.0f, -80.0f));
    m_objectShader->setMat4("projection", projection);
    m_objectShader->setMat4("view", view);



    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f)); 
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));	// it's a bit too big for our scene, so scale it down
    m_objectShader->setMat4("model", model);
    m_model->Draw(*m_objectShader);

    for(unsigned int i = 0; i < m_amount; i++) {
        m_objectShader->setMat4("model", m_modelMatrices[i]);
        m_rockModel->Draw(*m_objectShader);
    }

    return 0;
}