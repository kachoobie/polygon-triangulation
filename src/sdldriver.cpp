#include "../include/sdldriver.hpp"

SDLDriver::SDLDriver(int width, int height, const char *windowName, std::string fileName)
{
    windowWidth = width;
    windowHeight = height;
    this->fileName = fileName;

    window = SDL_CreateWindow(windowName, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
}

SDL_AppResult SDLDriver::drive()
{

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    std::vector<Point> vertices = this->readPolygon(this->fileName);
    std::vector<Point> correctedVertices = this->centerPolygon(vertices);
    Polygon polygon(correctedVertices);

    SDL_Event event;
    bool running = true;
    while(running) {
        SDL_RenderClear(this->renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.scancode == SDL_SCANCODE_P) {
                    std::cout << "Polyganizing..." << '\n';
                } else if (event.key.scancode == SDL_SCANCODE_RETURN) {
                    std::cout << "Triangulating..." << '\n';
                } 
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for (int i = 1; i < correctedVertices.size(); ++i) {
            Point start = correctedVertices.at(i - 1);
            Point end = correctedVertices.at(i);
            SDL_RenderLine(renderer, start.x, start.y, end.x, end.y);
        }
        Point finalStart = correctedVertices.at(correctedVertices.size() - 1);
        Point finalEnd = correctedVertices.at(0);
        SDL_RenderLine(renderer, finalStart.x, finalStart.y, finalEnd.x, finalEnd.y);

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }

    SDL_Quit();
    return SDL_APP_CONTINUE;
}

std::vector<Point> SDLDriver::readPolygon(std::string filePath)
{
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to load file." << std::endl;
    }

    std::vector<Point> vertices;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::vector<std::string> coord = this->splitLine(line);
        Point point(std::stof(coord.at(0)), std::stof(coord.at(1)));
        vertices.push_back(point);
    }

    inputFile.close();
    return vertices;
}

std::vector<Point> SDLDriver::centerPolygon(std::vector<Point> vertices)
{
    std::vector<Point> correctedVertices;

    Point firstPoint = vertices.at(0);
    float midpointY = this->windowHeight / 2.0;

    float minX, maxX, minY, maxY;
    minX = firstPoint.x;
    maxX = firstPoint.x;
    minY = firstPoint.y;
    maxY = firstPoint.y;

    std::vector<Point>::iterator iter;
    for (iter = vertices.begin() + 1; iter < vertices.end(); ++iter) {
        Point pt = *iter;
        if (pt.x < minX) {
            minX = pt.x;
        } else if (pt.x > maxX) {
            maxX = pt.x;
        }

        if (pt.y < minY) {
            minY = pt.y;
        } else if (pt.y > maxY) {
            maxY = pt.y;
        }
    }

    Point currentCenter((maxX + minX) / 2.0, (maxY + minY) / 2.0);
    Point correctedCenter(this->windowWidth / 2.0, this->windowHeight / 2.0);
    float xDiff = correctedCenter.x - currentCenter.x;
    float yDiff = correctedCenter.y - currentCenter.y;

    for (iter = vertices.begin(); iter < vertices.end(); ++iter) {
        Point currentPoint = *iter;
        float newY = 2 * midpointY - (currentPoint.y + yDiff);
        Point newPoint(currentPoint.x + xDiff, newY);
        correctedVertices.push_back(newPoint);
    }

    return correctedVertices;
}

std::vector<std::string> SDLDriver::splitLine(std::string line)
{
    std::stringstream ss(line);
    std::string coord;
    std::vector<std::string> coords;
    
    while (ss >> coord) {
        coords.push_back(coord);
    }
    
    return coords;
}