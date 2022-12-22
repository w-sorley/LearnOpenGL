#include "shader.h"

Shader::Shader(const GLchar* vertextPath, const GLchar* fragmentPath, const GLchar* geoPath){
    std::string vertexCode;
    std::string fragmentCode;
    std::string geoCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);


    try
    {
        vShaderFile.open(vertextPath);
        fShaderFile.open(fragmentPath);
        gShaderFile.open(geoPath);

        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close(); 
        gShaderFile.close(); 


        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        geoCode = gShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::File read failed!" << std::endl;
    }

    this->ID = GLUtils::CreateProgram(vertexCode.c_str(), fragmentCode.c_str(), geoCode.c_str());   
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name,float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
 
}