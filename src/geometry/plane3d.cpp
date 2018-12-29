#include "plane3d.hpp"

// ##############################################
// ### operators ################################
// ##############################################

Plane3d& Plane3d::operator=(const Plane3d &p) {
    if (this != &p) {
        base   = p.base;
        normal = p.normal;
        d      = p.d;
    }

    return *this;
}


// ##############################################
// ### others ###################################
// ##############################################

// v(x, y, z) point and p plane [n, b] with n unit vector, v2 normal intersection of v with p, distance:
// D = | n . (v - v2) |
//   = | n.v - n.v2 |
//   = | n.v - d | because d = - n.v2
// if p[N, b], D = | n.v - d | * 1 / | n |
// removing the | | of the nominator yields the "signed distance", eg:
//    - the distance D
//    - the sign being > 0 if the point is "above the normal side", < 0 if "under the normal side"
double Plane3d::get_signed_distance_from_point_to_plane(const Vector3d &v) const {
    return v * normal + d / normal.norm();
}

// #TODO: missing comment
bool Plane3d::handle_intersection_of_segment_with_plane(Vector3d &a, Vector3d &b) const {
    const double da = get_signed_distance_from_point_to_plane(a);
    const double db = get_signed_distance_from_point_to_plane(b);

    if (da < 0 && db < 0)
        return true;
    else if (da > 0 & db < 0) {
        double f = da / (da - db); // intersection factor (between 0 and 1)
        sf::Color new_color = sf::Color(a.color.r + f * (b.color.r - a.color.r),
                                        a.color.g + f * (b.color.g - a.color.g),
                                        a.color.b + f * (b.color.b - a.color.b));
        b = a + (b - a) * f;

        b.color = new_color;
    }
    else if (da < 0 & db > 0)
        handle_intersection_of_segment_with_plane(b, a);

    return false;
}

// #TODO: explain change point opacity
sf::Vertex Plane3d::get_projection_on_plane(const Vector3d &v,
                                            const unsigned window_width,
                                            const unsigned window_height) const {
    sf::Color vertex_color = v.color;

    vertex_color.a = map(get_signed_distance_from_point_to_plane(v), 0, PROJECTION_MAX_DEPTH, 255, 0); 

    return sf::Vertex(sf::Vector2f(PROJECTION_FACTOR * v.x / v.z + window_width  / 2,
                                   PROJECTION_FACTOR * v.y / v.z + window_height / 2),
                      vertex_color);
}
