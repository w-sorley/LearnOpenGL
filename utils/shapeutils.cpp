#include "shapeutils.h"


unsigned int VAO;
unsigned int lightVAO;
Shader* ShapeUtils::m_objectShader;
Shader* ShapeUtils::m_lightShader;
unsigned int diffuseMap;
unsigned int specularMap;
int ShapeUtils::init(){
    float cubeVertices[] = {
    // 后表面（z = -0.5）（可以根据顶点所属的面确定该点的法向量）
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glEnable(GL_DEPTH_TEST); // 开启深度测试

    // 配置顶点缓冲对象，传输顶点数据
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    // 配置顶点数组对象，指定数据的获取方式组织结构
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(void*)(3 * sizeof(float))); // 注意：此处最后一个参数的单位为字节（而不是数据个数）
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(void*)(6 * sizeof(float))); // 注意：此处最后一个参数的单位为字节（而不是数据个数）
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 解绑（bind的过程相当于钥匙，打开指定的箱子或挂载上，配置完成后然后锁上或卸载，下次再用时直接打开或再次挂载上即可使用）
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //配置纹理数据
    diffuseMap = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/container2.jpg"); 
    specularMap = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/container2_specular.jpg");

    m_objectShader =new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/vertex.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/fragment.shader");
    m_lightShader =new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/lightVertex.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/lightFragment.shader");

    m_objectShader->use();
    m_objectShader->setInt("material.diffuse", 0); // 设置采样器对应的纹理单元
    m_objectShader->setInt("material.specular", 1);

    return 0;
}
int ShapeUtils::Draw(){

    glm::vec3 lightPos = glm::vec3(0.2f, 0.8f, -0.7f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    // lightColor.x = sin(glfwGetTime() * 2.0f);
    // lightColor.y = sin(glfwGetTime() * 0.7f);
    // lightColor.z = sin(glfwGetTime() * 1.3f);
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.8f); // 降低影响
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.4f); // 很低的影响

    // draw object
     m_objectShader->use();
    // 更新一个uniform之前你必须先使用程序（调用glUseProgram)，因为它是在当前激活的着色器程序中设置uniform的
    glUniform3fv(glGetUniformLocation(m_objectShader->ID, "light.position"), 1,  glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(m_objectShader->ID, "light.ambient"), 1,  glm::value_ptr(ambientColor));
    glUniform3fv(glGetUniformLocation(m_objectShader->ID, "light.diffuse"), 1,  glm::value_ptr(diffuseColor));
    glUniform3fv(glGetUniformLocation(m_objectShader->ID, "light.specular"), 1,  glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

    glm::vec3 viewPos = glm::vec3(-0.6f, -0.4f, -0.7f);
    glUniform3fv(glGetUniformLocation(m_objectShader->ID, "viewPos"), 1,  glm::value_ptr(viewPos));
    glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
    glUniform3fv(glGetUniformLocation(m_objectShader->ID, "material.specular"), 1,  glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
    m_objectShader->setFloat("material.shininess", 32.0f);

    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f)); 
    model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(m_objectShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // 使用时需要先激活再绑定
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // draw light 
    m_lightShader->use();
    glUniform3fv(glGetUniformLocation(m_lightShader->ID, "lightColor"), 1,  glm::value_ptr(lightColor));
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));   
    glUniformMatrix4fv(glGetUniformLocation(m_lightShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    return 0;
}