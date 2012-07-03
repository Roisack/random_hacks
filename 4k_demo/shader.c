#include "shader.h"
#include <stdio.h>
struct Shader s1;
struct Shader* s1_ptr = &s1;
void doShader()
{
    s1_ptr->vs_source = loadSource("coolShader.vs");
    s1_ptr->fs_source = loadSource("coolShader.fs");
    fprintf(stderr, "%s\n**%s\n**", s1_ptr->vs_source, s1_ptr->fs_source);
    compile();
}

char* loadSource(const char* filename)
{
    FILE* filePtr;
    char* buffer = NULL;
    int count = 0;
    if (filename != NULL)
    {
        filePtr = fopen(filename, "rt");
        if (filePtr != NULL)
        {
            fprintf(stderr, "Opened file %s\n", filename);
            fseek(filePtr, 0, SEEK_END);
            count = ftell(filePtr);
            rewind(filePtr);

            if (count > 0)
            {
                buffer = (char *)malloc(sizeof(char) * (count+1));
                count = fread(buffer,sizeof(char),count,filePtr);
                buffer[count] = '\0';
            }
            fclose(filePtr);
        }
        else
        {
            fprintf(stderr, "Could not open file %s\n", filename);
        }
    }
    return buffer;
}

void compile()
{
    fprintf(stderr, "Compiling\n");
    s1_ptr->vs_handle = glCreateShader(GL_VERTEX_SHADER);
    s1_ptr->fs_handle = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* vs_src = s1_ptr->vs_source;
    const GLchar* fs_src = s1_ptr->fs_source;
    char* infoLog;
    int infoLogLength = 0;  

    glShaderSource(s1_ptr->vs_handle, 1, &vs_src, NULL);
    glShaderSource(s1_ptr->fs_handle, 1, &fs_src, NULL);

    fprintf(stderr, "---\n\n%s\n\n%s\n\n", s1_ptr->vs_source, s1_ptr->fs_source);

    glCompileShader(s1_ptr->vs_handle);
    printShaderInfoLog(s1_ptr->vs_handle);

    int dummy = glGetError();

    if (!(glGetError() == GL_NO_ERROR))
    {
        fprintf(stderr, "Error compiling vertex shader %d\n", glGetError());
    }

    glCompileShader(s1_ptr->fs_handle);
    printShaderInfoLog(s1_ptr->fs_handle);
    if (!(glGetError() == GL_NO_ERROR))
    {
        fprintf(stderr, "Error compiling fragment shader %d\n", glGetError());
    }

    s1_ptr->shader_handle = glCreateProgram();
    glAttachShader(s1_ptr->shader_handle, s1_ptr->vs_handle);
    glAttachShader(s1_ptr->shader_handle, s1_ptr->fs_handle);
    glLinkProgram(s1_ptr->shader_handle);
    printProgramInfoLog(s1_ptr->shader_handle);
}

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        fprintf(stderr, "%s\n",infoLog);
        free(infoLog);
    }
}

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}

void destroyShader()
{
    fprintf(stderr, "Destroying shader\n");
    glDeleteProgram(s1_ptr->shader_handle);
    glDeleteShader(s1_ptr->vs_handle);
    glDeleteShader(s1_ptr->fs_handle);
    fprintf(stderr, "Freeing source\n");
    free(s1_ptr->vs_source);
    fprintf(stderr, "Freeing source\n");
    free(s1_ptr->fs_source);
    fprintf(stderr, "Shader destroyed\n");
}

void useShader()
{
    glUseProgram(s1_ptr->shader_handle);
}

void unuseShader()
{
    glUseProgram(0);
}

