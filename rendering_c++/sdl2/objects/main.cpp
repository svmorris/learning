#include <SDL.h>
#include <cmath>
#include <iostream>

# define BG_COLOUR 0, 0, 0

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


class Rectangle
{
public:
    int x;
    int y;
    int r;
    int g;
    int b;
    int a;
    int r_height;
    int r_width;

    Rectangle(Window *_window, int _x, int _y, int _r_height, int _r_width, int _r, int _g, int _b, int _a):
        window(*_window), x(_x), y(_y), r(_r), g(_g), b(_b), a(_a), r_height(_r_height), r_width(_r_width)
    {
    }

    void draw()
    {
        for (int i = x; i < x+r_width; i++)
        {
            for (int j = y; j < y+r_height; j++)
            {
                window.draw_pixel(i, j, r, g, b, a);
            }
        }
    }

private:
    Window window;

};



int main (int argc, char **argv)
{
    int widnow_width = 1000;
    int window_height = 500;


    // Create window
    Window window(window_height, widnow_width);


    // Variable that stores events like quit
    SDL_Event event;

    Rectangle square(&window, 0, 0, 100, 100, 255, 255, 0, 255);
    Rectangle rectangle(&window, 0, 0, 100, 200, 255, 0, 255, 255);

    window.clear();
    window.render();
    while (!(event.type == SDL_QUIT))
    {
        SDL_Delay(10);
        SDL_PollEvent(&event);


        // logic
        square.r_width++;
        square.r_height++;
        // rectangle.r_height++;
        rectangle.x++;
        rectangle.x++;
        rectangle.y++;

        window.clear();
        square.draw();
        rectangle.draw();
        window.render();
    }
}

