#ifndef __SHADER_HPP_
#define __SHADER_HPP_

#include <GL/glew.h>
#include <string>
#include <stdio.h>

class Shader
{
private:
    int id;
    char* vs_source;
    char* fs_source;
    GLuint vs_handle;
    GLuint fs_handle;
    GLuint shader_handle;
public:
    Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
    ~Shader();

    char* loadSource(const char* filepath);
    void compile();
    int printOpenglError(char *file, int line);
    void printShaderInfoLog(GLuint obj);
    void printProgramInfoLog(GLuint obj);

    void use();
    void unuse();
};

#endif

