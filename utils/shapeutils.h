#ifndef SHAPE_UTILS
#define SHAPE_UTILS

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "glutils.h"
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class ShapeUtils
{
private:
    static Shader* m_shader;

public:
    ShapeUtils(/* args */);
    ~ShapeUtils();

    static int DrawTriangle(GLFWwindow *window);
    static int init(GLFWwindow *window);
    static int updateCameraPos(GLFWwindow *window);
};

#endif