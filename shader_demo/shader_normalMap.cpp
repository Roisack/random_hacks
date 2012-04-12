#include "shader_normalMap.hpp"
#include "manager.hpp"

ShaderNormalMap::ShaderNormalMap(const char* vs_filepath, const char* fs_filepath) : Shader(vs_filepath, fs_filepath)
{
    fprintf(stderr, "ShaderNormalMap onstructing\n");
}

ShaderNormalMap::~ShaderNormalMap()
{
}

void ShaderNormalMap::update()
{
    use();
    set_int("size_x", 1024);
    set_int("size_y", 1024);
    set_float("time", manager.getTime()*10);

}

void ShaderNormalMap::action1()
{
}

void ShaderNormalMap::action2()
{
}

void ShaderNormalMap::action3()
{
}

void ShaderNormalMap::action4()
{
}

void ShaderNormalMap::action5()
{
}

void ShaderNormalMap::action6()
{
}

void ShaderNormalMap::action7()
{
}

void ShaderNormalMap::action8()
{
}
