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

GLuint GLUtils::CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource, const char *pGeoShaderSource){
    unsigned int program = 0;
    GLuint vertextShader = LoadShader(GL_VERTEX_SHADER, pVertexShaderSource);
    if(!vertextShader) return program;
    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if(!fragmentShader) return program;
    GLuint geoShader = LoadShader(GL_GEOMETRY_SHADER, pGeoShaderSource);
    if(!geoShader) return program;

    program = glCreateProgram();
    if(program) {
        glAttachShader(program, vertextShader);
        glAttachShader(program, fragmentShader);
        glAttachShader(program, geoShader);
        glLinkProgram(program);
        glDetachShader(program, vertextShader);
        glDetachShader(program, fragmentShader);
        glDetachShader(program, geoShader);

        
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
    glDeleteShader(geoShader);


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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image, &width, &height, &nrChannels, 0);
    if(data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        // 自动生成多级渐远
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "ERROR::Load image failed!"  << std::endl;
    }
    
    stbi_image_free(data);
    return texture;
}
unsigned int GLUtils::createTextureFromFile(const char *path, const char *dir){
    char filePath[1024] = "";
    strcat(filePath, dir);
    strcat(filePath, "/");
    strcat(filePath, path);
    GLuint ret = createTexture(filePath);
    return ret;
}
GLuint GLUtils::createCubeTexture(std::vector<std::string> files){
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    int width, height, nrChannels;
    for(unsigned int i = 0; i < files.size(); i++) {
        unsigned char *data = stbi_load(files[i].c_str(), &width, &height, &nrChannels, 0);
        if(data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "ERROR::TEXTURE: locad texture image file failed." << std::endl;
        }
        stbi_image_free(data);
    }

    return texture;
}