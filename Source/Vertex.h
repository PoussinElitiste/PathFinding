#ifndef VERTEX_H
#define VERTEX_H

#include <cmath>

struct Vertex
{
    Vertex() : x{}, y{}, z{}
    {}

    Vertex(double iX, double iY, double iZ) :
        x(iX), y(iY), z(iZ)
    {}

    inline double length() const { return std::sqrt(x * x + y * y + z * z); }

    inline double length2() const { return x * x + y * y + z * z; }

    double x, y, z;
};

inline Vertex operator+(const Vertex& v0, const Vertex& v1) { return Vertex(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z); }

inline Vertex operator-(const Vertex& v0, const Vertex& v1) { return Vertex(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z); }

#endif // VERTEX_H
