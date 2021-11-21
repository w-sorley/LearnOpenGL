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