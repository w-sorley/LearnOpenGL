#include "shapeutils.h"
#include "shadersource.h"

const char *VERTEX_SHADER = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 vertexColor;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "    vertexColor = aColor;\n"
        "}\0";
        
const char *FRAGMENT_SHADER = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 vertexColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(vertexColor, 1.0);\n"
        "}\0";

GLuint ShapeUtils::program = 0;

unsigned int VAO;

int ShapeUtils::init(){
    float vertices[] = {
        0.5f,   -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,   0.5f,  0.0f, 0.0f, 0.0f, 1.0f,   
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };


    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

  

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    program = GLUtils::CreateProgram(VERTEX_SHADER, FRAGMENT_SHADER);
}
int ShapeUtils::DrawTriangle(){

    float tiemValue = glfwGetTime();
    float blueValue = (sin(tiemValue) / 2.0) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(program, "ourColor");
    glUseProgram(program);
    glUniform4f(vertexColorLocation, 0.0, 0.0, blueValue, 0.0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
    return 0;
}