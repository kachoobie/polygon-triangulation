#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

#include "polygon.hpp"

class SDLDriver
{
    public:
        int windowWidth, windowHeight;
        std::string fileName;
        SDLDriver(int windowWidth, int windowHeight, const char *windowName, std::string fileName);
        SDL_AppResult drive();
        std::vector<Point> readPolygon(std::string filePath);

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        std::vector<Point> centerPolygon(std::vector<Point> vertices);
        std::vector<std::string> splitLine(std::string line);
};