#include "shapeutils.h"


Shader* ShapeUtils::m_objectShader;
Shader* ShapeUtils::m_plantShader;
Model* ShapeUtils::m_model;
Model* ShapeUtils::m_rockModel;
glm::mat4* ShapeUtils::m_modelMatrices;
unsigned int ShapeUtils::m_amount = 300;
int ShapeUtils::init(){
    glEnable(GL_DEPTH_TEST); // 开启深度测试

    m_objectShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/vertex.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/fragment.shader");
    m_plantShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/plant.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/fragment.shader");
    m_model = new Model("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/obj/planet/planet.obj");
    m_rockModel = new Model("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/obj/rock/rock.obj");

    m_modelMatrices = new glm::mat4[m_amount];
    srand(static_cast<unsigned int>(glfwGetTime())); // 设置随机数生成器的种子
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

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, m_amount * sizeof(glm::mat4), &m_modelMatrices[0], GL_STATIC_DRAW);

    for(unsigned int i = 0; i < m_rockModel->meshes.size(); i++) {
        unsigned int VAO = m_rockModel->meshes[i].VAO;
        glBindVertexArray(VAO);

        // 顶点属性最大允许的数据大小等于一个vec4,一个mat4本质上是4个vec4
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)( 2 * sizeof(glm::vec4) ));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)( 3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1); // 每绘制一个instance更新一次（顶点属性的内容至新一组数据）
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }

    return 0;
}

int ShapeUtils::Draw(){


    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 1000.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -10.0f, -80.0f));

    m_objectShader->use();
    m_objectShader->setMat4("projection", projection);
    m_objectShader->setMat4("view", view);
    
    m_plantShader->use();
    m_plantShader->setMat4("projection", projection);
    m_plantShader->setMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f)); 
    model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));	// it's a bit too big for our scene, so scale it down
    m_plantShader->setMat4("model", model);
    m_model->Draw(*m_plantShader);


    m_objectShader->use();
    m_objectShader->setInt("texture_diffuse1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_rockModel->textures_loaded[0].ID);
    for(unsigned int i = 0; i < m_rockModel->meshes.size(); i++) {
        glBindVertexArray(m_rockModel->meshes[i].VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(m_rockModel->meshes[i].indices.size()), GL_UNSIGNED_INT, 0, m_amount);
        glBindVertexArray(0);
    }

    return 0;
}