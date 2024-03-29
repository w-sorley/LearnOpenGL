#include "shapeutils.h"

unsigned int VAO;
unsigned texture1, texture2;
Shader* ShapeUtils::m_shader;
Camera* ShapeUtils::m_camera;

double lastXPos = 0;
double lastYPos = 0;
bool firstFrame = true;
float deltaTime = 0.0f;
float lastTime  = 0.0f;
void mouse_callback(GLFWwindow *window, double xPos, double yPos){

    if(firstFrame)
    {
        lastYPos = yPos;
        lastXPos = xPos;
        firstFrame = false;
    }
    double xOffset = xPos - lastXPos;
    double yOffset = lastYPos - yPos;
    lastYPos = yPos;
    lastXPos = xPos;

    ShapeUtils::m_camera->ProcessMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    ShapeUtils::m_camera->ProcessMouseScroll(yoffset);
}
int ShapeUtils::init(GLFWwindow *window){
    float vertices[] = {
    // location.x, location.y, location.z, textcoord.x, textcoord.y
    // a cube have 36 vertices(6 surface x 2 triangle per surface x 3 vertices per tr )
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    glEnable(GL_DEPTH_TEST); // 开启深度测试
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 鼠标输入
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    texture1 =  GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/box.jpg");
    texture2 =  GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/froot.jpg");

    m_shader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/vertex.shader", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/fragment.shader");
    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    return 0;
}

int ShapeUtils::updateCameraPos(GLFWwindow *window) {
    float current = glfwGetTime();
    deltaTime = current - lastTime;
    lastTime = current;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboard(RIGHT, deltaTime);

    m_shader->setMat4("lookAt", m_camera->GetViewMatrix());
    return 0;
}



int ShapeUtils::DrawTriangle(GLFWwindow *window){

    m_shader->setInt("texture1", 0);
    m_shader->setInt("texture2", 1);
    m_shader->use();

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 0.0f,  0.5f, -0.5f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    updateCameraPos(window);

    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = glm::mat4(1.0f);
    // projection decide what can show on the screen
    projection = glm::perspective(glm::radians(m_camera->Zoom), (float)7.0f / (float)8.0f, 0.1f, 100.0f);
    // by default, the model at origin point
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // pass transformation matrices to the shader
    m_shader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    m_shader->setMat4("view", view);
    int length = sizeof(cubePositions)/sizeof(cubePositions[0]);
    for(int i = 0; i < length; i++){
        glm::mat4 model = glm::mat4(1.0f);
        float angle = 20.0f * (i); 
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        model  = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        m_shader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // glBindVertexArray(0);
    return 0;
}