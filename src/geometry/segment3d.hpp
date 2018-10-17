#ifndef SEGMENT_3D_HPP
#define SEGMENT_3D_HPP

#include "vector3d.hpp"

class Segment3d {
private:
    Vector3d a, b;

public:
    // constructors
    Segment3d() : a(Vector3d()), b(Vector3d()) {}
    Segment3d(const Vector3d &_a, const Vector3d &_b) : a(_a), b(_b) {}
    Segment3d(const Vector3d &_a, const Vector3d &_b, const sf::Color _color) : a(_a, _color), b(_b, _color) {}
    Segment3d(const Segment3d &s) : a(s.a), b(s.b) {}

    // operators
    Segment3d& operator=(const Segment3d &s);


friend class Plane3d;
friend class Solid3d;
friend class Camera3d;
};

#endif
