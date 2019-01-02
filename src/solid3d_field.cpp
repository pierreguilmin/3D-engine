#include "solid3d_field.hpp"

// ##############################################
// ### others ###################################
// ##############################################

void Solid3dField::render(sf::RenderWindow &window,
                          const unsigned window_width,
                          const unsigned window_height,
                          const Camera3d &camera) const {
    for (auto s : solids)
        s.render_solid(window, window_width, window_height, camera);
}

void Solid3dField::move() {
    for (size_t i = 0; i < solids.size(); ++i)
        solids[i].rotate(rotation_axes[i], rotation_speeds[i]);
}
