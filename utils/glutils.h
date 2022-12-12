#ifndef GL_UTILS
#define GL_UTILS

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "std_image.h"

class GLUtils
{
private:
    /* data */
    static const int INFO_LOG_LENGTH = 512;
public:
    GLUtils(/* args */);
    ~GLUtils();
    
    static GLuint LoadShader(GLenum shaderType, const char *pSource);
    
    static GLuint CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource);

    static GLuint createTexture(const char *image);

    static unsigned int  createTextureFromFile(const char *path, const char *dir);
};
#endif