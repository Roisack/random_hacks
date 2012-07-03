#include <GL/gl.h>
#include <SDL/SDL.h>
#include "shader.h"
#include "surface.h"

void _start()
{

    int w = 800;
    int h = 600;

    SDL_Event e;

    SDL_SetVideoMode(w, h, 32, SDL_OPENGL | SDL_RESIZABLE);

    createSurface(1024, 1024);
  
    do {
        SDL_PollEvent(&e);

        glClearColor(0.7f, 0.0f, 0.0f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluPerspective(65, w/h, 0.1, 1100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
        
        updateSurface();
        renderSurface();
        SDL_GL_SwapBuffers();
    } while (e.type != SDL_KEYDOWN);

    destroyShader();
    destroySurface();

    fprintf(stderr, "Exiting\n");
    asm ( \
      "movl $1,%eax\n" \
      "xor %ebx,%ebx\n" \
      "int $128\n" \
    );
}

