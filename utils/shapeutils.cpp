#include "shapeutils.h"


Shader* ShapeUtils::m_objectShader;
Shader* ShapeUtils::m_singleColorShader;
Shader* ShapeUtils::m_rectangleShader;
unsigned int ShapeUtils::cubeVAO;
unsigned int ShapeUtils::cubeTexture;
unsigned int ShapeUtils::planeVAO;
unsigned int ShapeUtils::floorTexture;
unsigned int ShapeUtils::grassVAO;
unsigned int ShapeUtils::grassTexture;
unsigned int ShapeUtils::fbo;
unsigned int ShapeUtils::textColorBuffer;
unsigned int ShapeUtils::rectangleVAO;
int ShapeUtils::init(){
    // glEnable(GL_DEPTH_TEST); // 开启深度测试
    // 设置深度测试使用的比较函数
    // glDepthFunc(GL_ALWAYS);

    // 模版测试
    // glEnable(GL_STENCIL_TEST);

    // 开启混合（透明）
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC1_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 指定混合方程的影响因子

    //开启面剔除,注意顶点数据的定义顺序
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_FRONT); // 决定剔除前向面还是背向面
    // glFrontFace(GL_CW);  // 定义前向面是顺时针还是逆时针


   float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};
    float planeVertices[] = {
        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f								
    };

    float transparentVertices[] = {
        // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
    };

    float rectangleVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    unsigned int cubeVBO;
    glGenBuffers(1, &cubeVBO);
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int planeVBO;
    glGenBuffers(1, &planeVBO);
    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int grassVBO;
    glGenBuffers(1, &grassVBO);
    glGenVertexArrays(1, &grassVAO);
    glBindVertexArray(grassVAO);
    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), &transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);

    unsigned int rectangleVBO;
    glGenBuffers(1, &rectangleVBO);
    glGenVertexArrays(1, &rectangleVAO);
    glBindVertexArray(rectangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glBindVertexArray(0);

    m_objectShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/depthTesting.vs", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/depthTesting.fs");
    m_rectangleShader = new Shader("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/rectangle.vs", "/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/shaders/rectangle.fs");
 


    cubeTexture  = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/marble.jpg");
    floorTexture = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/metal.jpg");
    // grassTexture = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/grass.png");
    grassTexture = GLUtils::createTexture("/Users/w_sorley/Workspace/C_CPP/OpenGL/utils/image/blending_transparent_window.png");
    m_objectShader->use();
    m_objectShader->setInt("texture1", 0);
    m_rectangleShader->use();
    m_rectangleShader->setInt("screenTexture", 0);

    // 生成帧缓冲对象

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // 生成纹理
    glGenTextures(1, &textColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // 分配内存
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textColorBuffer, 0); //将纹理附加到当前绑定的帧缓冲对象
    // 渲染帧缓冲（储存源格式）
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 600, 800); //分配内存
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); ////将制定渲染缓冲对象附加到当前绑定的帧缓冲对象
    // bind完附件之后检查完整性
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER: framebuffer is not complete." << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    
    return 0;
}

int ShapeUtils::Draw(){
    // 使用自定义的帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_objectShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(-1.2f, 0.0f, -5.5f));  
    // view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f)); 
    glm::mat4 projection = glm::perspective(glm::radians(100.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    m_objectShader->setMat4("view", view);
    m_objectShader->setMat4("projection", projection);

    // floor
    glStencilMask(0x00);
    glBindVertexArray(planeVAO);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    m_objectShader->setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // cubes
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cubeTexture); 	
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
    m_objectShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.3f));
    m_objectShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // vector<glm::vec3> vegetation;
    // vegetation.push_back(glm::vec3( -0.15f,  0.0f,  3.51f));
    // vegetation.push_back(glm::vec3( 0.0f,  0.0f,  3.7f));
    // vegetation.push_back(glm::vec3( -0.5f,  0.0f, 3.6f));
    // vegetation.push_back(glm::vec3(-0.2f,  0.0f, 3.3f));
    // vegetation.push_back(glm::vec3(-0.025f,  0.0f, 3.18f));

    // glBindVertexArray(grassVAO);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, grassTexture);
    // for (unsigned int i = 0; i < vegetation.size(); i++)
    // {
    //     model = glm::mat4(1.0f);
    //     model = glm::translate(model, vegetation[i]);
    //     model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));               
    //     m_objectShader->setMat4("model", model);
    //     glDrawArrays(GL_TRIANGLES, 0, 6);
    // }

    // 使用默认的帧缓冲
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    // 绘制四边形
    m_rectangleShader->use();
    glBindVertexArray(rectangleVAO);
    glBindTexture(GL_TEXTURE_2D, textColorBuffer); //使用帧缓冲的bind的纹理附件
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    return 0;
}