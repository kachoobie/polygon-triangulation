#ifndef POINT
#define POINT

struct Point
{
    float x;
    float y;
    Point (float xCoor, float yCoor)
    {
        x = xCoor;
        y = yCoor;
    }
};

#endif