// Source: https://iq.opengenus.org/getting-started-2d-graphics-in-cpp-sdl2/
#include <SDL.h>

class Framework
{
public:
    // Constructor to initialise window
    Framework(int _height, int _width): height(_height), width(_width)
    {
        SDL_Init(SDL_INIT_VIDEO); // initialise sdl as video
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // set draw colour
        SDL_RenderClear(renderer); // clear the new window
        SDL_RenderPresent(renderer); // Reflects the changes done in the window
    }

    // Destructor
    ~Framework()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit;
    }

private:
    // window dimensions
    int height;
    int width;

    // pointer for renderer
    SDL_Renderer *renderer = NULL;
    // pointer for window
    SDL_Window *window = NULL;

};



int main (int argc, char *argv[])
{
    // Creating the window object
    Framework fw(atoi(argv[1]), atoi(argv[2]));

    // variable for handling events
    // Somehow this event gets set
    // when something happens to the
    // sdl window / renderer.
    SDL_Event event;

    //We can just check if the window terminated in a loop
    while(!(event.type == SDL_QUIT))
    {
        SDL_Delay(10); // setting some delay
        SDL_PollEvent(&event); // Catching the poll event
    }
}
