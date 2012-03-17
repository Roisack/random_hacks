/*
This class contains a sprite. It is created either by
1. Defining a resolution
2. Defining a path to an image file
The sprite can be used by either SDL or OpenGL. The constructor first builds an SDL_Surface,
then constructs a new glTexture2D with the pixel data from the SDL_Surface.
The default rendering function puts the texture on a flat 2D plane and maps the texture on it.
The model is then rendered at coordinates (x,y,z)

There are some operations that are performed on the sprite pixel data. After each of these
operations the glTexture2D is reseted and re-created, so the operations are somewhat heavy.
convertToGrayscale() is one of them.
*/

#include "sprite.hpp"
#include "toolbox.hpp"
#include "opengl.hpp"
#include <assert.h>
#include <cmath>
#include "manager.hpp"

#include <boost/thread.hpp> // Sticking with boost threads since Bill's compiler doesn't have proper C++11 support yet
boost::mutex mutex_lock;
int threads_ready = 0;

Sprite::Sprite()
{
}

// Constructs a sprite with some size. Useful for shaders
Sprite::Sprite(int sizeX, int sizeY)
{
    w = sizeX;
    h = sizeY;
    x = 0;
    y = 0;
    scale = 1.0;
    id = 0;
    glGenTextures(1, &id);
    assert(id);
    opacity = 1.0f;
    name = tbox.resolutionToString(w, h);
    rotation = 0.0f;
    
    glBindTexture(GL_TEXTURE_2D, id);
    
    GLuint target = GL_TEXTURE_2D;
    spriteSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
    
    // Get the texture format. We will want to create it according to the SDL surface
    format = checkGeneric(spriteSurface);
    
    // Lock the surface for direct pixel acccess
    SDL_LockSurface(spriteSurface);
    
    SDL_Color color;
    
    // Init the surface with random colors. Useful for debugging
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            color = tbox.getRandomColor();
            setPixel(spriteSurface, i, j, color);
        }
    }
    
    // Done, unlock
    SDL_UnlockSurface(spriteSurface);
    
    // Create the actual OpenGL texture
    glTexImage2D(target,
        0,
        format,
        spriteSurface->w,
        spriteSurface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        spriteSurface->pixels);

    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    fprintf(stderr, "New sprite built with following properties: Generic sprite %s\n", name.c_str());
}

// Constructs a sprite based on a loaded image file. Good for textures
Sprite::Sprite(std::string &path) :
    x(0), y(0)
{
    x = 1;
    y = 1;
    w = 1024;
    h = 1024;
    opacity = 1;
    scale = 0.1;
    id = 0;
    glGenTextures(1, &id);
    assert(id);
    opacity = 1.0f;
    glBindTexture(GL_TEXTURE_2D, id);
    name = path;
    rotation = 0.0f;

    col.r = 1.0f;
    col.g = 1.0f;
    col.b = 1.0f;

    GLuint target = GL_TEXTURE_2D;
    bool buildMipmaps = true;
    spriteSurface = NULL;
    fprintf(stderr, "Loading: %s\n", path.c_str());
    if (target == GL_TEXTURE_2D)
    {
        spriteSurface = IMG_Load(path.c_str());
        std::string error = IMG_GetError();
        fprintf(stderr, "IMG_Load returns: %s\n", error.c_str());
        format = check(spriteSurface, path);
        if (format == GL_RGBA)
            useAlpha = true;
        else
            useAlpha = false;
        w = spriteSurface->w;
        h = spriteSurface->h;
        
        glTexImage2D(target,
            0,
            format,
            spriteSurface->w,
            spriteSurface->h,
            0,
            format,
            GL_UNSIGNED_BYTE,
            spriteSurface->pixels);
        
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    fprintf(stderr, "New sprite built with following properties: data sprite %s, %d%s%d, use alpha: %d\n", name.c_str(), w, "x", h, useAlpha);
}

Sprite::~Sprite()
{
    assert(spriteSurface);
    fprintf(stderr, "Sprite destructing: %s\n", name.c_str());
    SDL_FreeSurface(spriteSurface);
}

// When constructing, make sure the input file is good
GLenum Sprite::check(SDL_Surface *surface, std::string &path)
{
    if (!surface) {
        fprintf(stderr, "Surface is empty: %s\n", path.c_str());
        throw std::string("SDL surface error:") += path;
    }
    
    /*if ((surface->w & (surface->w - 1)) != 0 ||
        (surface->h & (surface->h - 1)) != 0) {
        SDL_FreeSurface(surface);
        fprintf(stderr, "Image size not in power of two\n");
        throw "Image size must be in power of two";
    }
    */
    // Select textures format
    GLenum format;
    if (surface->format->BytesPerPixel == 4)
        format = GL_RGBA;
    else if (surface->format->BytesPerPixel == 3)
        format = GL_RGB;
    else if (surface->format->BytesPerPixel == 1)
        format = GL_LUMINANCE;
    else {
        SDL_FreeSurface(surface);
        throw "Image format must be 8, 24 or 32 bits per pixel.";
    }
    return format;
}

GLenum Sprite::checkGeneric(SDL_Surface* pSurface)
{
    // Select texture format
    GLenum format;
    if (pSurface->format->BytesPerPixel == 4) {
        format = GL_RGBA;
    }
    else if (pSurface->format->BytesPerPixel == 3)
    {
        format = GL_RGB;
    }
    else if (pSurface->format->BytesPerPixel == 1) {
        format = GL_LUMINANCE;
    }
    else {
        SDL_FreeSurface(pSurface);
        throw "Image format must be 8, 24 or 32 bits per pixel.";
    }
    return format;
}

// Sets one pixel of a SDL_Surface to desired colour
void Sprite::setPixel(SDL_Surface *pSurface, int x, int y, SDL_Color color)
{
    Uint32 col = SDL_MapRGB(pSurface->format, color.r, color.g, color.b);
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(pPosition, &col, pSurface->format->BytesPerPixel);
}

// Sets one pixel of a SDL_Surface to desired colour
void setPixelOffClass(SDL_Surface *pSurface, int x, int y, SDL_Color color)
{
    Uint32 col = SDL_MapRGB(pSurface->format, color.r, color.g, color.b);
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(pPosition, &col, pSurface->format->BytesPerPixel);
}

// Set all pixels of a surface to one color
void Sprite::setAllPixels(SDL_Surface* pSurface, SDL_Color col)
{
    SDL_LockSurface(spriteSurface);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            setPixel(pSurface, i, j, col);
        }
    }

    SDL_UnlockSurface(spriteSurface);
    regenerateTexture();
}

// Builds a new OpenGL texture2D from the SDL_Surface->pixels
void Sprite::regenerateTexture()
{
    GLuint target = GL_TEXTURE_2D;
    id = 0;
    glGenTextures(1, &id);
    assert(id);
    glBindTexture(GL_TEXTURE_2D, id);
    format = checkGeneric(spriteSurface);

    glTexImage2D(target,
        0,
        format,
        spriteSurface->w,
        spriteSurface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        spriteSurface->pixels);
    
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

float Interpolate(float x0, float x1, float alpha)
{
   float out = x0 * (1.0 - alpha) + alpha * x1;
   return out;
}

float** Sprite::generateBaseNoise()
{
    float** baseNoise;
    baseNoise = new float*[w];
    for (int i = 0; i < w; i++)
    {
        baseNoise[i] = new float[h];
    }
    
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            baseNoise[i][j] = 1.0/float(tbox.giveRandomInt(1,100));
        }
    }

    return baseNoise;
}

void appendFinishedTexture(float*** container, int index, float** texture)
{
    mutex_lock.lock();
    container[index] = texture;
    threads_ready++;
    fprintf(stderr, "Appending finished texture at octave %d\n", index);
    mutex_lock.unlock();
}

void reportReady()
{
    mutex_lock.lock();
    fprintf(stderr, "Thread reporting ready: %d", threads_ready);
    threads_ready++;
    fprintf(stderr, " - New value: %d\n", threads_ready);
    mutex_lock.unlock();
}

// Sets elements from start to stop to some value for array arr
// The last parameter is a pointer to the function used for doing the calculation
void calculateSmoothNoiseElements(float** arr, float** baseNoise, int start_x, int stop_x, int start_y, int stop_y, int octave, int width, int height)
{
    int samplePeriod = 1 << octave;
    float sampleFrequency = 1.0f / float(samplePeriod);

    for (int i = start_x; i < stop_x; i++)
    {
        int sample_i0 = (i / samplePeriod) * samplePeriod;
        int sample_i1 = (sample_i0 + samplePeriod) % width;
        float horizontal_blend = (i - sample_i0) * sampleFrequency;

        for (int j = start_y; j < stop_y; j++)
        {
            int sample_j0 = (j / samplePeriod) * samplePeriod;
            int sample_j1 = (sample_j0 + samplePeriod) % height;
            float vertical_blend = (j -sample_j0) * sampleFrequency;

            float top = Interpolate(baseNoise[sample_i0][sample_j0], baseNoise[sample_i1][sample_j0], horizontal_blend);
            float bottom = Interpolate(baseNoise[sample_i0][sample_j1], baseNoise[sample_i1][sample_j1], horizontal_blend);
            arr[i][j] = Interpolate(top, bottom, vertical_blend);
        }
    }
    reportReady();
}

void Sprite::generateSmoothNoise(float** baseNoise, int octave, float*** container, int width, int height)
{
    float** smoothNoise = tbox.giveFloatArray2D(width, height);

    // The computation for making the smooth noise texture is multithreaded
    // Each thread will handle a slice of the texture from some x1 to x2, and y values from 0 to the end of the array, h
    int number_of_threads = 8;
    int work_per_thread = floor(float(w) / float(number_of_threads));
    std::vector<boost::thread*> threadContainer;
    threads_ready = 0;

    for (int i = 0; i < number_of_threads; i++)
    {
        boost::thread noiseGenerator(calculateSmoothNoiseElements, smoothNoise, baseNoise, i*work_per_thread, (i+1)*work_per_thread, 0, h, octave, w, h);
        boost::thread* threadPtr = &noiseGenerator;
        threadContainer.push_back(threadPtr);
    }

    fprintf(stderr, "Waiting for threads to finish at octave %d\n", octave);

    while (threads_ready < number_of_threads)
    {
    }

    fprintf(stderr, "Joining threads for octave %d\n", octave);
    std::vector<boost::thread*>::iterator iter;
    for (iter = threadContainer.begin(); iter != threadContainer.end(); iter++)
    {
        (*iter)->join();
    }

    appendFinishedTexture(container, octave, smoothNoise);
}

void mergeNoises(float amplitude, int octave, float*** smoothNoises, float** perlinNoise, 
                 SDL_Surface* out, int start_x, int stop_x, int start_y, int stop_y)
{
    SDL_Color temp;
    for (int i = start_x; i < stop_x; i++)
    {
        for (int j = start_y; j < stop_y; j++)
        {
            perlinNoise[i][j] += smoothNoises[octave][i][j] * amplitude;
            temp.r = perlinNoise[i][j]*255;
            temp.g = temp.r;
            temp.b = temp.r;
            setPixelOffClass(out, i, j, temp);
        }
    }
    reportReady();
}

SDL_Surface* Sprite::generatePerlinNoise(float** baseNoise, int octaveCount)
{
    int width = w;
    int height = h;

    // 3 dimensional container for the 2D slices of noise
    float*** smoothNoises = tbox.giveFloatArray3D(octaveCount, w, h);

    float persistence = 1.00;
 
    // Generate instances of smooth noise, based on the octave
    // They are slices in our 3D "cube". Voxels of sort

    for (int i = 0; i < octaveCount; i++)
    {
        generateSmoothNoise(baseNoise, i, smoothNoises, width, height);
    }

    float** perlinNoise = tbox.giveFloatArray2D(width, height);
    tbox.clearFloatArray2D(perlinNoise, width, height);
    float amplitude = 1.5f;
    float totalAmplitude = 0.0f;

    SDL_Color temp;
    SDL_Surface* out = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);

    int number_of_threads = 8;
    int work_per_thread = floor(float(w) / float(number_of_threads));
    std::vector<boost::thread*> threadContainer;
    threads_ready = 0;

    // Blend all the slices of the noise together into one 2D slice
    // This is multithreaded too. Each thread handles texture slices from some x1 to some x2
    for (int octave = octaveCount - 1; octave >= 0; octave--)
    {
        amplitude *= persistence;
        totalAmplitude += amplitude;
        threads_ready = 0;

        for (int i = 0; i < number_of_threads; i++)
        {
            boost::thread noiseMerger(mergeNoises, amplitude, octave, smoothNoises, perlinNoise, out, i*work_per_thread, (i+1)*work_per_thread, 0, h);
            boost::thread* threadPtr = &noiseMerger;
            threadContainer.push_back(threadPtr);
        }

        fprintf(stderr, "Waiting for threads to finish at octave %d\n", octave);

        while (threads_ready < number_of_threads)
        {
        }

        fprintf(stderr, "Joining threads for octave %d\n", octave);
        std::vector<boost::thread*>::iterator iter;
        for (iter = threadContainer.begin(); iter != threadContainer.end(); iter++)
        {
            (*iter)->join();
        }
    }

    /*
    //normalisation
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            perlinNoise[i][j] /= totalAmplitude;
        }
    }
    */
    
    return out;
}

// Creates some perlin noise
void Sprite::createClouds()
{
    // Note: This is HIGHLY unoptimzied for two reasons:
    // 1) I still haven't grasped Perlin noise completely, and wish to learn it as I go.
    //    Most of this stuff I found with random googling and implemented it as I could
    // 2) I want to experiment with multithreading and see the performance increase.
    //    Eventually I hope to do this on a fragment shader
    convertToGreyScale();
    float** base = generateBaseNoise();
    spriteSurface = generatePerlinNoise(base, 10);
    regenerateTexture();
}

// Returns a SDL_Color of a specific pixel in a SDL_Surface
SDL_Color Sprite::getPixel(SDL_Surface *pSurface, int x, int y)
{
    SDL_Color color;
    Uint32 col = 0;
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return color;
}

void Sprite::convertToGreyScale()
{
    SDL_LockSurface(spriteSurface);
    SDL_Color colorBW;
    
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            colorBW = tbox.getBWColor(getPixel(spriteSurface, i, j));
            setPixel(spriteSurface, i, j, colorBW);
        }
    }
    SDL_UnlockSurface(spriteSurface);
    regenerateTexture();
}

void Sprite::bind(int unit)
{
    assert(unit >= 0 && unit < 8);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Sprite::unbindAll()
{
    for (int i=0; i<8; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Sprite::render()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(x, y, 0);
    glScalef(scale, scale, scale);
    glRotatef(rotation, 0, 0, 1);
    
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, id);
    glColor4f(col.r, col.g, col.b, opacity);
    
    if (useAlpha)
    {
	    glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	    glBlendEquation(GL_ADD);
    } else
    {
        glDisable(GL_BLEND);
    }

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-w, -h);
        glTexCoord2f(1, 1); glVertex2f(w, -h);
        glTexCoord2f(1, 0); glVertex2f(w, h);
        glTexCoord2f(0, 0); glVertex2f(-w, h);
    glEnd();
    
    glPopMatrix();
}
