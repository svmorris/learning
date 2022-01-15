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

    void render_present()
    {
        SDL_RenderPresent(renderer);
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

    }

    void clear_window()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
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

    // variables
    int circle_radius = window_width/100;
    int x = circle_radius;
    int y = circle_radius;

    //We can just check if the window terminated in a loop
    while(!(event.type == SDL_QUIT))
    {
        SDL_Delay(10); // setting some delay
        SDL_PollEvent(&event); // Catching the poll event

        if (x >= window_width-circle_radius)
        {
            x = circle_radius;
            y += circle_radius;
        }
        if (y > window_height-circle_radius)
        {
            x = circle_radius;
            y = circle_radius;
        }
        fw.clear_window();
        fw.draw_circle(x, y, circle_radius, 255, 255, 255);
        fw.render_present();
        x += 10;
    }
}
