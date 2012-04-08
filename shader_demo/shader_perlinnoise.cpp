#include "shader_perlinnoise.hpp"
#include "manager.hpp"

ShaderPerlinNoise::ShaderPerlinNoise(const char* vs_filepath, const char* fs_filepath) : Shader(vs_filepath, fs_filepath)
{
    fprintf(stderr, "ShaderPerlinNoise constructing\n");
    baseNoise = boost::shared_ptr<Sprite>(new Sprite(1024,1024));
    amplitude = 1.0f;
    persistence = 1.1f;
    octaveSetter = 1;
    magicNumber1 = 1;
    magicNumber2 = 1;
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
    set_float("persistence", persistence);  // Defines how persistent each octave is
    set_float("amplitude", amplitude);      // Defines at what amplitude each octave appears
    set_int("octaveSetter", octaveSetter);  // Defines how many octaves of noise are calculated
    set_int("magicNumber1", magicNumber1);  // Defines an offset for the noise
    set_int("magicNumber2", magicNumber2);  // Defines how much the random noise appears over the simplex noise
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
    octaveSetter++;
}

void ShaderPerlinNoise::action4()
{
    octaveSetter--;
}

void ShaderPerlinNoise::action5()
{
    magicNumber1 += 1;
}

void ShaderPerlinNoise::action6()
{
    magicNumber1 -= 1;
}

void ShaderPerlinNoise::action7()
{
    magicNumber2 += 1;
}

void ShaderPerlinNoise::action8()
{
    magicNumber2 -= 1;
}
