#ifndef PLANE_3D_HPP
#define PLANE_3D_HPP

#include "segment3d.hpp"

#define PROJECTION_FACTOR 1024.0
#define PROJECTION_MAX_DEPTH 800

class Plane3d {
private:
    Vector3d base;
    Vector3d normal;
    
public:
    // constructors
    Plane3d() : base(Vector3d()), normal(Vector3d()) {}
    Plane3d(const Vector3d &_base, const Vector3d &_normal) : base(_base), normal(_normal) {}
    Plane3d(const Plane3d &p) : base(p.base), normal(p.normal) {}

    // operators
    Plane3d& operator=(const Plane3d &p);

    // others
    double get_equation_value_of_d() const;
    double signed_distance_from_point_to_plane(const Vector3d &v) const;
    bool handle_intersection_of_segment_with_plane(Segment3d &s) const;
    sf::Vertex get_projection_on_plane(const Vector3d &v, const unsigned window_width, const unsigned window_height) const;
};

#endif
