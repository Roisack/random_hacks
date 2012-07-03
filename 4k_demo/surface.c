#include "surface.h"
#include "gekko_math.h"

struct Surface* render_base_ptr;

void setPixel(SDL_Surface* pSurface, int x, int y, SDL_Color color)
{
    Uint32 col = SDL_MapRGB(pSurface->format, color.r, color.g, color.b);
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(pPosition, &col, pSurface->format->BytesPerPixel);
}

void createSurface(int w, int h)
{
    render_base_ptr->height = h;
    render_base_ptr->width = w;
    render_base_ptr->id = 0;
    glGenTextures(1, &render_base_ptr->id);
    render_base_ptr->opacity = 1.0f;
    glBindTexture(GL_TEXTURE_2D, render_base_ptr->id);
    GLuint target = GL_TEXTURE_2D;
    SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, render_base_ptr->width, render_base_ptr->height, 32, 0, 0, 0, 0);
    render_base_ptr->format = GL_RGBA;
    SDL_LockSurface(temp);
    SDL_Color col;
    int i, j;
    for (i = 0; i < render_base_ptr->width; i++)
    {
        for (j = 0; j < render_base_ptr->height; j++)
        {
            col.r = linear_interpolation(0, render_base_ptr->width, i);
            col.g = linear_interpolation(0, render_base_ptr->height, j);
            col.b = i;
            setPixel(temp, i, j, col);
        }
    }
    SDL_UnlockSurface(temp);

    glTexImage2D(target, 0, render_base_ptr->format, render_base_ptr->width, render_base_ptr->height, 0, render_base_ptr->format, GL_UNSIGNED_BYTE, temp->pixels);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void destroySurface()
{
}

void renderSurface()
{
}

void updateSurface()
{
}

