#include <GL/gl.h>

struct Shader
{
    char* vs_source;
    char* fs_source;
    GLuint shader_handle;
    GLuint vs_handle;
    GLuint fs_handle;
};

void doShader();
char* loadSource();
void compile();

void useShader();
void unuseShader();

void destroyShader();

