#include "shader_perlinnoise.hpp"
#include "manager.hpp"

ShaderPerlinNoise::ShaderPerlinNoise(const char* vs_filepath, const char* fs_filepath) : Shader(vs_filepath, fs_filepath)
{
    fprintf(stderr, "ShaderPerlinNoise constructing\n");
    baseNoise = boost::shared_ptr<Sprite>(new Sprite(1024,1024));
    amplitude = 1.0f;
    persistence = 1.1f;
}

ShaderPerlinNoise::~ShaderPerlinNoise()
{
}

void ShaderPerlinNoise::update()
{
    use();
    set_int("size_x", 1024);
    set_int("size_y", 1024);
    set_float("time", manager.getTime());
    set_float("persistence", persistence);
    set_float("amplitude", amplitude);
    baseNoise->bind(0);
    set_int("baseNoise", 0);
}

void ShaderPerlinNoise::action1()
{
    amplitude += 0.3f;
}

void ShaderPerlinNoise::action2()
{
    amplitude -= 0.3f;
}

void ShaderPerlinNoise::action3()
{
    persistence += 0.3f;
}

void ShaderPerlinNoise::action4()
{
    persistence -= 0.3f;
}
