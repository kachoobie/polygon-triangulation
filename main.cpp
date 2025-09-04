#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "include/sdldriver.hpp"

int main(int argc, char *argv[])
{
    int windowWidth = 1024, windowHeight = 768;
    const char *windowName = "Polygon Triangulation";
    std::string fileName = argv[1];
    SDLDriver driver(windowWidth, windowHeight, windowName, fileName);

    driver.drive();

    return 1;
}