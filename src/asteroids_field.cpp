#include "asteroids_field.hpp"

// ##############################################
// ### constructors #############################
// ##############################################

AsteroidsField::AsteroidsField(const Vector3d &center,
                               const unsigned density,
                               const int radius) {
    for (unsigned i = 0; i < density; ++i) {
        Vector3d offset(rand(-radius, radius), rand(-radius, radius), rand(-radius, radius));
        asteroids.push_back(Asteroid3d(center + offset, rand(10, 50), 2));

        rotation_axes.push_back(Vector3d(rand(0.0, 1.0), rand(0.0, 1.0), rand(0.0, 1.0)));
        rotation_speeds.push_back(rand(1, 5));
    }
}


// ##############################################
// ### others ###################################
// ##############################################

void AsteroidsField::render_objects(sf::RenderWindow &window,
                                    const unsigned window_width,
                                    const unsigned window_height,
                                    const Camera3d &camera) const {
    for (auto a : asteroids)
        a.render_solid(window, window_width, window_height, camera);
}

void AsteroidsField::move_objects() {
    for (size_t i = 0; i < asteroids.size(); ++i)
        asteroids[i].rotate(rotation_axes[i], rotation_speeds[i]);
}
