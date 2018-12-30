#ifndef PLANE_3D_HPP
#define PLANE_3D_HPP

#include "vector3d.hpp"
#include "segment3d.hpp"

#define PROJECTION_FACTOR    1024.0
#define PROJECTION_MAX_DEPTH 800

class Plane3d {
private:
    Vector3d base;
    Vector3d normal;

    // p(x, y, z) in plane [n(a, b, c), b] ⟺ n . (p - b)        = 0
    //                                     ⟺ n.p - n.b          = 0
    //                                     ⟺ ax + by + cz - n.b = 0 ⟹ d = - n.b
    double d;
    
public:
    // constructors
    Plane3d() : base(Vector3d()), normal(Vector3d()), d(0.0) {}
    Plane3d(const Vector3d &_base,
            const Vector3d &_normal) : base(_base),
                                       normal(_normal),
                                       d(- (_normal * _base)) {}
    Plane3d(const Plane3d &p) : base(p.base), normal(p.normal), d(p.d) {}

    // operators
    Plane3d& operator=(const Plane3d &p);

    // others
    double get_signed_distance_from_point_to_plane(const Vector3d &v) const;
    bool handle_intersection_of_segment_with_plane(Vector3d &a, Vector3d &b) const;
    sf::Vertex get_projection_on_plane(const Vector3d &v,
                                       const unsigned window_width,
                                       const unsigned window_height) const;
};

#endif
