// Source: https://iq.opengenus.org/getting-started-2d-graphics-in-cpp-sdl2/
#include <SDL.h>
#include <cmath>

#include <cstdlib>
#include <unistd.h>

class Framework
{
public:
    // Constructor to initialise window
    Framework(int _height, int _width): height(_height), width(_width)
    {
        SDL_Init(SDL_INIT_VIDEO); // initialise sdl as video
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        // Set the base colour of the window
        // NOTE: the tutorial uses 0 for the opacity of the window,
        // this is fine as gnome doesn't seem to support transparent
        // windows the same way. On Awesome-wm they seem to be
        // supported better and if the opacity is not set to 255 then 
        // the window will actually be opaque.
        // (could also be that awesome supports them worse)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

    void draw_circle(int center_x, int center_y, int _radius, int r, int g, int b)
    {
        // setting the colour to be blue and 100% opaque
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);

        // Drawing circle
        for (int x=center_x-_radius; x <= center_x+_radius; x++)
        {
            for (int y=center_y-_radius; y<=center_y+_radius; y++)
            {
                if((std::pow(center_y-y, 2) + std::pow(center_x-x, 2)) <= std::pow(_radius, 2))
                    SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        SDL_RenderPresent(renderer);
    }

    void draw_square(int x, int y, int r, int g, int b, int size)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        for (int i = x; i < x+size; i++)
        {
            for (int j = y; j < y+size; j++)
            {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
        SDL_RenderPresent(renderer);
    }
    void clear_window()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
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
    int window_height = 1080;
    int window_width = 2560;
    // Creating the window object
    Framework fw(window_height, window_width);



    // variable for handling events
    // Somehow this event gets set
    // when something happens to the
    // sdl window / renderer.
    SDL_Event event;

    //We can just check if the window terminated in a loop
    int x = 0;
    int y = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    int counter = 0;
    while(!(event.type == SDL_QUIT))
    {
        SDL_Delay(10); // setting some delay
        SDL_PollEvent(&event); // Catching the poll event

        x = 1 + (rand() % window_width);
        y = 1 + (rand() % window_height);
        r = 1 + (rand() % 255);
        b = 1 + (rand() % 255);
        g = 1 + (rand() % 255);
        fw.draw_square(x, y, r, g, b, 100);
        if (counter > 1000)
        {
            fw.clear_window();
            counter = 0;
        }
        counter++;
    }
}
