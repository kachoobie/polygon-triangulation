#include <vector>
#include <string>
#include "point.hpp"
#include "triangle.hpp"

class Polygon
{

    public:
        std::vector<Point> vertices;
        Polygon(std::vector<Point> vertices);
        ~Polygon();
        std::vector<Triangle> triangulate();
    private:
};