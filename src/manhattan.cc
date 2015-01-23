#include <cstdio>

#include <SDL.h>

int main(int argc, char** argv) {
  //The window we'll be rendering to
  SDL_Window* window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;

  //Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return -1;
  }
  else
  {
    //Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
      //Get window surface
      screenSurface = SDL_GetWindowSurface(window);

      bool running = true;
      Uint32 ticks = SDL_GetTicks();
      SDL_Event e;
      Uint32 fps = 60;
      Uint32 mspf = 1000/fps;
      Uint32 target_ticks = mspf;

      Uint32 t = 0;

      while (running) {
        ticks = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            running = false;
          } else if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
              running = false;
            }
          }
        }

        SDL_Rect rect;
        rect.x = ++++t;
        rect.y = t;
        rect.w = 100;
        rect.h = 100;

        //Fill the surface white
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x0, 0x0, 0x0));
        SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xFF-t, t, 0xFF));

        //Update the surface
        SDL_UpdateWindowSurface(window);

        Uint32 elapsed_ticks = SDL_GetTicks() - ticks;
        Uint32 ticks_to_sleep = target_ticks - elapsed_ticks;

        ticks = SDL_GetTicks();
        int tick_delta;

        if (ticks_to_sleep > 0) {
          SDL_Delay(ticks_to_sleep);
          Uint32 slept_ticks = SDL_GetTicks() - ticks;
          tick_delta = slept_ticks - ticks_to_sleep;
        } else {
          tick_delta = -static_cast<int>(ticks_to_sleep);
        }

        target_ticks = mspf - tick_delta;
      }
    }
  }

  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
