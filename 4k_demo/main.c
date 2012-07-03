#include <GL/gl.h>
#include <SDL/SDL.h>
#include "shader.h"
#include "surface.h"

void _start()
{
    doShader();
    useShader();

    int* v, x, y, w = 320, h = 240, i = 0;

    SDL_Surface* b;
    SDL_Event e;

    b = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL);    
    v = b->pixels;
  
    do {
        SDL_PollEvent(&e);

        for (y = 0; y < h; ++y)
        { 
            for (x = 0; x < w; ++x) 
                v[y * w + x] = (x+i) ^ y;
        }
        SDL_Flip(b);
        ++i;




    } while (e.type != SDL_KEYDOWN);

    destroyShader();

    asm ( \
      "movl $1,%eax\n" \
      "xor %ebx,%ebx\n" \
      "int $128\n" \
    );
}

