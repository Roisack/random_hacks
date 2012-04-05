#ifndef __SHADER_INTERFERENCE_HPP_
#define __SHADER_INTERFERENCE_HPP_

#include "shader.hpp"

class ShaderInterference : public Shader
{
private:
    int id;
public:
    ShaderInterference(const char* vs_filepath, const char* fs_filepath);
    ~ShaderInterference();
    void update();
};

#endif
