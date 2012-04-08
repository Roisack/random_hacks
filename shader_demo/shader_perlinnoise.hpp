#ifndef __SHADER_PERLINNOISE_HPP_
#define __SHADER_PERLINNOISE_HPP_

#include "shader.hpp"
#include "sprite.hpp"
#include <boost/shared_ptr.hpp>

class ShaderPerlinNoise : public Shader
{
private:
    int id;
    boost::shared_ptr<Sprite> baseNoise;
    float persistence;
    float amplitude;
public:
    ShaderPerlinNoise(const char* vs_filepath, const char* fs_filepath);
    ~ShaderPerlinNoise();
    void update();
    void action1();
    void action2();
    void action3();
    void action4();
};

#endif
