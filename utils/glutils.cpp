#include "glutils.h"

GLuint GLUtils::LoadShader(GLenum shaderType, const char *pSource) {
    unsigned int shader = 0;
    shader = glCreateShader(shaderType);
    if(!shader) return shader;

    glShaderSource(shader, 1, &pSource, NULL);
    glCompileShader(shader);
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infoLog[INFO_LOG_LENGTH];
        glGetShaderInfoLog(shader, INFO_LOG_LENGTH, NULL, infoLog);
        std::cout << "ERROR::Compile Shader Failed, InfoLog = "<< infoLog << std::endl;
        shader = 0;
    }
    
    return shader;
}

GLuint GLUtils::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource){
    unsigned int program = 0;
    GLuint vertextShader = LoadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if(!vertextShader) return program;
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if(!fragmentShader) return program;

    program = glCreateProgram();
    if(program) {
        glAttachShader(program, vertextShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glDetachShader(program, vertextShader);
        glDetachShader(program, program);

        int status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if(!status) {
            char infoLog[INFO_LOG_LENGTH];
            glGetProgramInfoLog(program, INFO_LOG_LENGTH, NULL, infoLog);
            std::cout << "ERROR::Link Program Failed, InfoLog = " << infoLog << std::endl;
            program = 0;
        }
    }
    glDeleteShader(vertextShader);
    glDeleteShader(fragmentShader);

    return program;
}

GLuint GLUtils::createTexture(const char* image){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 设置环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // 设置过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // 自动生成多级渐远
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR::Load image failed!" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}