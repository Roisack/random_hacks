#include "surface.h"
#include "gekko_math.h"
#include "shader.h"

struct Surface surface;
struct Surface* render_base_ptr = &surface;

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
    fprintf(stderr, "Creating surface\n");
    render_base_ptr->height = h;
    render_base_ptr->width = w;
    render_base_ptr->id = 0;
    fprintf(stderr, "glGenTextures\n");
    glGenTextures(1, &render_base_ptr->id);
    render_base_ptr->opacity = 1.0f;
    fprintf(stderr, "glBindTexture\n");
    glBindTexture(GL_TEXTURE_2D, render_base_ptr->id);
    GLuint target = GL_TEXTURE_2D;
    fprintf(stderr, "SDL_CreateRGBSurface\n");
    SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, render_base_ptr->width, render_base_ptr->height, 32, 0, 0, 0, 0);
    render_base_ptr->format = GL_RGBA;
    SDL_LockSurface(temp);
    SDL_Color col;
    int i, j;
    fprintf(stderr, "Filling SDL surface\n");
    for (i = 0; i < render_base_ptr->width; i++)
    {
        for (j = 0; j < render_base_ptr->height; j++)
        {
            col.r = 0.5f;//linear_interpolation(0, render_base_ptr->width, i);
            col.g = 0.5f;//linear_interpolation(0, render_base_ptr->height, j);
            col.b = i;
            setPixel(temp, i, j, col);
        }
    }
    SDL_UnlockSurface(temp);

    fprintf(stderr, "Creating opengl texture\n");
    glTexImage2D(target, 0, render_base_ptr->format, render_base_ptr->width, render_base_ptr->height, 0, render_base_ptr->format, GL_UNSIGNED_BYTE, temp->pixels);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    doShader();
    useShader();
}

void destroySurface()
{
    fprintf(stderr, "Destroying surface\n");
}

void renderSurface()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glColor4f(1.0f, 1.0f, 1.0f, render_base_ptr->opacity);

    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_ADD);
    
    useShader();

    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex2f(-render_base_ptr->width, -render_base_ptr->height);
        glTexCoord2f(1, 1); glVertex2f(render_base_ptr->width, -render_base_ptr->height);
        glTexCoord2f(1, 0); glVertex2f(render_base_ptr->width, render_base_ptr->height);
        glTexCoord2f(0, 0); glVertex2f(-render_base_ptr->width, render_base_ptr->height);
    glEnd();
    unuseShader();
    glPopMatrix();
}

void updateSurface()
{
}

