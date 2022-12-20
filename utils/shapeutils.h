#ifndef SHAPE_UTILS
#define SHAPE_UTILS

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "glutils.h"
#include "shader.h"
#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>


class ShapeUtils
{
private:
    static Shader* m_objectShader;
    static Shader* m_singleColorShader;
    static Shader* m_rectangleShader;
    static Model*  m_model;
    static unsigned int cubeVAO;
    static unsigned int planeVAO;
    static unsigned int cubeTexture;
    static unsigned int floorTexture;
    static unsigned int grassVAO;
    static unsigned int grassTexture;
    static  unsigned int fbo;
    static unsigned int textColorBuffer;
    static unsigned int rectangleVAO;

public:
    ShapeUtils(/* args */);
    ~ShapeUtils();

    static int Draw();
    static int init();
};

#endif