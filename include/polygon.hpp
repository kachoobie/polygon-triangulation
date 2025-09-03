#include <vector>
#include "point.hpp"
#include "triangle.hpp"

class Polygon
{

    public:
        std::vector<Point> vertices;
        Polygon(std::vector<Point>);
        ~Polygon();
        std::vector<Triangle> triangulate();
    private:

};