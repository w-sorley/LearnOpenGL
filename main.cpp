#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "shapeutils.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(int argc, const char *argv[])
{
    // 环境初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // 创建窗口对象
    GLFWwindow* window = glfwCreateWindow(600, 800, "LearnOpenGL", NULL, NULL); // 创建窗口对象
    if(NULL == window) {
        std::cout << "create opengl window failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //将窗口上下文设置为当前线程上下文

    // 初始化GLAD:加载系统相关的OpenGL函数指针地址
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to init GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    
    ShapeUtils::init();
    // 循环使窗口保持
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // 渲染执行
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //设置清空屏幕所使用的颜色
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除颜色缓冲(屏幕被设置为上面设置的颜色)
        ShapeUtils::DrawTriangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();    
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);   
}

void processInput(GLFWwindow *window) {
    // 监测espace退出键是否按下
    if(GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, true);
    }
}

