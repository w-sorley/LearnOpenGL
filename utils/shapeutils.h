#ifndef SHAPE_UTILS
#define SHAPE_UTILS

#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "glutils.h"
#include "shader.h"


class ShapeUtils
{
private:
    static Shader* m_shader;

public:
    ShapeUtils(/* args */);
    ~ShapeUtils();

    static int DrawTriangle();
    static int init();
};

#endif