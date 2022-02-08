#include <iostream>
#include <vector>
#include <SDL2/SDL.h>


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
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit;
    }

    void draw_pixel(int x, int y, int r, int g, int b, int o)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, o);
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


struct Pixel
{
    int x;
    int y;
};

struct Colour
{
    int r;
    int g;
    int b;
};


/*
 * The Object class is the parent
 * class of all things rendered
 * to the screen.
 *
 * It handles properties and functions that
 * are universal to all child objects.
 */
class Object
{
private:
    Window window;
public:
    Colour colour;
    // Array of all pixels of the object.
    std::vector<Pixel> pixels;

    Object(Window *_window, Colour _color):
        window(*_window), colour(_color) {}

    void draw()
    {
        for (int i = 0; i < pixels.size(); i++)
            window.draw_pixel(pixels[i].x, pixels[i].y, colour.r, colour.g, colour.b, 0);
    }

    void move(int x, int y)
    {
        for (int i = 0; i < pixels.size(); i++)
        {
            pixels[i].x += x;
            pixels[i].y += y;
        }
    }
};


class Rectangle: public Object
{
public:
    int side_x;
    int side_y;

    Rectangle(Window *window, Pixel _base, Colour colour, int _side_x, int _side_y):
        Object(window, colour), side_x(_side_x), side_y(_side_y)
    {
        calc_pixels(_base);
    }


private:
    /*
     * Function to calculate where each pixel
     * lies and add it to the pixel vector.
     */
    void calc_pixels(Pixel base)
    {
        // Drawing a rectangle by looping over each
        // pixel in a nested for loop, and adding
        // each to the array.
        for (int ix = base.x; ix < side_x; ix++)
            for (int iy = base.y; iy < side_y; iy++)
                pixels.push_back({ix, iy});
    }

    // void increase_size(xa, ya)
};


class Circle: public Object
{
public:
    int radius;

    Circle(Window *window, Pixel _base, Colour colour, int _radius):
        Object(window, colour), radius(_radius)
    {
        calc_pixels(_base);
    }

private:
    void calc_pixels(Pixel base)
    {
        for (int x = base.x - radius; x <= base.y + radius; x++)
            for (int y = base.y - radius; y <= base.y + radius; y++)
                if((std::pow(base.y-y, 2) + std::pow(base.x-x, 2)) <= std::pow(radius, 2))
                    pixels.push_back({x, y});
    }

};



int main(int argc, char **argv)
{
    int window_height = 500;
    int window_width  = 1000;

    // Create the window
    Window window(window_height, window_width);

    // Variable to store sdl events like quit
    // SDL_Event event;

    window.clear();

    Rectangle rect(&window, {10, 10}, {255, 255, 255}, 100, 100);
    rect.draw();
    Circle circle(&window, {150, 150}, {255, 0, 0}, 50);
    circle.draw();

    window.render();

    std::cin.get();
}
