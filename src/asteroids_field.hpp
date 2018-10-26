#ifndef ASTEROIDS_FIELD_HPP
#define ASTEROIDS_FIELD_HPP

#include "utils/tools.hpp"
#include "geometry/vector3d.hpp"
#include "geometry/geometry.hpp"

class AsteroidsField {
private:
    std::vector<Asteroid3d> asteroids;
    std::vector<Vector3d> rotation_axes;
    std::vector<unsigned> rotation_speeds;

public:
    // constructors
    AsteroidsField(const Vector3d &center,
                   const unsigned density,
                   const int radius);

    // others
    void render_objects(sf::RenderWindow &window,
                        const unsigned window_width,
                        const unsigned window_height,
                        const Camera3d &camera) const;
    void move_objects();
};


#endif
