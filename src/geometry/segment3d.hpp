#ifndef SEGMENT_3D_HPP
#define SEGMENT_3D_HPP

#include <SFML/Graphics.hpp>
#include "vector3d.hpp"

class Segment3d {
private:
    size_t i, j;
    
public:
    // constructors
    Segment3d() : i(0), j(0) {}
    Segment3d(const size_t _i, const size_t _j) : i(_i), j(_j) {}
    Segment3d(const Segment3d &s) : i(s.i), j(s.j) {}

    // operators
    Segment3d& operator=(const Segment3d &s);

    // others
    Vector3d& get_a(std::vector<Vector3d> &points) const { return points[i]; }
    Vector3d& get_b(std::vector<Vector3d> &points) const { return points[j]; }


friend class Plane3d;
friend class Solid3d;
friend class Camera3d;
};

#endif
