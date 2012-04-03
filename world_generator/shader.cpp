#include "shader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

Shader::Shader(const char* vs_filepath, const char* fs_filepath)
{
    if (!vs_filepath || !fs_filepath)
    {
        fprintf(stderr, "Error at creating shader, missing a source file");
    }

    loadSource(vs_filepath, &vs_source);
    loadSource(fs_filepath, &fs_source);
    compile();
}

Shader::~Shader()
{
    glDeleteProgram(shader_handle);
    glDeleteShader(vs_handle);
    glDeleteShader(fs_handle);
}

void Shader::loadSource(const char* filepath, std::string* buffer)
{
    char temp[1024*8];
    FILE* filePtr = fopen(filepath, "r");
    if (!filePtr)
    {
        fprintf(stderr, "Error opening file %s\n", filepath);
    }
    
    int n = fread(temp, 1, sizeof(temp)-1, filePtr);
    temp[n] = '\n';
    fclose(filePtr);

    *buffer = temp;
}

void Shader::compile()
{
    vs_handle = glCreateShader(GL_VERTEX_SHADER);
    fs_handle = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* vs_src = vs_source.c_str();
    const GLchar* fs_src = fs_source.c_str();

    glShaderSource(vs_handle, 1, &vs_src, NULL);
    glShaderSource(fs_handle, 1, &fs_src, NULL);

    glCompileShader(vs_handle);
    if (!(glGetError() == GL_NO_ERROR))
    {
        fprintf(stderr, "Error compiling vertex shader\n");
    }
    glCompileShader(fs_handle);
    if (!(glGetError() == GL_NO_ERROR))
    {
        fprintf(stderr, "Error compiling fragment shader\n");
    }

    shader_handle = glCreateProgram();
    glAttachShader(shader_handle, vs_handle);
    glAttachShader(shader_handle, fs_handle);

    glLinkProgram(shader_handle);
    glUseProgram(shader_handle);
}

