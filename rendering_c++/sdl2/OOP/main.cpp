#include <iostream>
#include <vector>
#include <SDL.h>


#define BG_COLOUR 0, 0, 0


class Window
{
public:
    Window(int _height, int _width): height(_height), width(_width)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, BG_COLOUR, 255);
        SDL_RenderPresent(renderer);
    }

    ~Window()
    {
        std::cin.get();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit;
    }

    void draw_pixel(int x,  int y, int r, int g, int b, int a)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderDrawPoint(renderer, x, y);
    }

    void clear()
    {
        SDL_SetRenderDrawColor(renderer, BG_COLOUR, 255);
        SDL_RenderClear(renderer);
    }

    void render()
    {
        SDL_RenderPresent(renderer);
    }

private:
    int height;
    int width;

    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;
};




class Object
{
public:
    //vector array of pixdl cordinates

    Object(Window *_window): window(*_window)
    {

    }


    void move(int x, int y)
    {
        // add x and y to each element x and y in the vector of pixels
    }
    

private:
    Window window;
    
    void draw()
    {
        //for i in vetor array draw pixels
    }    
}


class Rectangle: public Object
{

}




int main(int argc, char **argv)
{
    int window_height = 1000;
    int window_width  = 500;

    // Create the window
    Window window(window_height, window_width);

    // Variable to store sdl events like quit
    SDL_Event event;

    

    window.clear();
    window.render();
}