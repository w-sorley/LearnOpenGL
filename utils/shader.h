#ifndef SHADER_SOURCE
#define SHADER_SOURCE
#include <glad.h>
#include "iostream"
#include "string"
#include "fstream"
#include "sstream"
#include "glutils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    /* data */
public:
    unsigned int ID;
    
    Shader(const GLchar* vertextPath, const GLchar* fragmentPath);

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name,float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
};
#endif




// "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "    \n"
//     "}\0";
