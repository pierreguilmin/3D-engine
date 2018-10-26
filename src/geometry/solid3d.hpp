#ifndef SOLID_3D_HPP
#define SOLID_3D_HPP

#include <SFML/Graphics.hpp>
#include "vector3d.hpp"
#include "segment3d.hpp"
#include "plane3d.hpp"
#include "camera3d.hpp"

class Solid3d {
public:
    enum class SOLID_TYPE {CUBE, SPHERE};

private:
    sf::VertexArray figure;

protected:
    std::vector<Segment3d> edges;
    Vector3d center;
    double max_size = -1.0;

public:
    // constructors
    Solid3d() { figure.setPrimitiveType(sf::Lines); }

    // operators
    Solid3d operator+=(const Solid3d &solid);
    Solid3d operator+(const Vector3d &v) const;
    Solid3d operator+=(const Vector3d &v);

    // others
    void set_max_size(const double _max_size) { max_size = _max_size; }
    void get_max_size();
    void add_segment(const Segment3d &s) { edges.push_back(s); }
    void render_solid(sf::RenderWindow &window, const unsigned window_width, const unsigned window_height, const Camera3d &camera);
    void clear() { edges.clear(); }
    void rotate_around_vector(const Vector3d rotation_center, const Vector3d &axis, const double theta);
    void rotate(const Vector3d &axis, const double theta);
};

#endif
