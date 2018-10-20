#ifndef SOLID_3D_HPP
#define SOLID_3D_HPP

#include "vector3d.hpp"
#include "segment3d.hpp"
#include "plane3d.hpp"
#include "camera3d.hpp"

class Solid3d {
public:
    enum class SOLID_TYPE {CUBE, SPHERE};

public:
    std::vector<Segment3d> edges;
    sf::VertexArray figure;
    Vector3d center;

public:
    // constructors
    Solid3d() { figure.setPrimitiveType(sf::Lines); }
    Solid3d(const SOLID_TYPE type, const string &parameters_string);

    // operators
    Solid3d operator+=(const Solid3d &solid);
    Solid3d operator+(const Vector3d &v) const;
    Solid3d operator+=(const Vector3d &v);

    // others
    void set_center(const Vector3d &_center);
    void add_segment(const Segment3d &s) { edges.push_back(s); }
    void render_solid(sf::RenderWindow &window, const unsigned window_width, const unsigned window_height, const Camera3d &camera);
    void clear() { edges.clear(); }
    void rotate(const Vector3d &rotation_center, const Vector3d &axis, const double theta, const bool object_axis = false);

};

#endif
