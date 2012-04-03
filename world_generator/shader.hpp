#ifndef __SHADER_HPP_
#define __SHADER_HPP_

#include <GL/glew.h>
#include <string>
#include <stdio.h>

class Shader
{
private:
    int id;
    std::string vs_source;
    std::string fs_source;
    GLuint vs_handle;
    GLuint fs_handle;
    GLuint shader_handle;
public:
    Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
    ~Shader();

    void loadSource(const char* filepath, std::string* buffer);
    void compile();
};

#endif

