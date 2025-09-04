#include "../include/polygon.hpp"

Polygon::Polygon(std::vector<Point> vertices)
{
    this->vertices = vertices;
}

Polygon::~Polygon(){}

std::vector<Triangle> Polygon::triangulate()
{
    std::vector<Triangle> triangles;

    return triangles;
}