#include "solid3d.hpp"

// ##############################################
// ### operators ################################
// ##############################################

Solid3d Solid3d::operator+=(const Solid3d &solid) {
    for (auto s : solid.edges)
        this -> add_segment(s);

    return *this;
}

Solid3d Solid3d::operator+(const Vector3d &v) const {
    Solid3d new_solid(*this);

    for (auto &s : new_solid.edges)
        s += v;

    new_solid.center += v;

    return new_solid;
}

Solid3d Solid3d::operator+=(const Vector3d &v) {
    for (auto &s : edges)
        s += v;

    center += v;

    return *this;
}


// ##############################################
// ### others ###################################
// ##############################################

void Solid3d::get_max_size() {
    for (auto s : edges)
        max_size = std::max({max_size, (s.a - center).norm(), (s.b - center).norm()});
}

// #TODO: missing comment
void Solid3d::render_solid(sf::RenderWindow &window, const unsigned window_width, const unsigned window_height, const Camera3d &camera) {

    // check if center is too far from frustrum
    for (auto side : camera.frustrum) {
        const Vector3d temp_center = camera.transform_vector(center);
        if (side.get_signed_distance_from_point_to_plane(temp_center) <= - max_size)
            return;
    }

    figure.clear();

    for (auto s : edges) {
        bool outside_frustrum = false;
        s = camera.transform_segment(s);

        for (auto side : camera.frustrum) {
            outside_frustrum = side.handle_intersection_of_segment_with_plane(s);
            if (outside_frustrum)
                break;
        }

        if (! outside_frustrum) {
            figure.append(camera.frustrum[0].get_projection_on_plane(s.a, window_width, window_height));
            figure.append(camera.frustrum[0].get_projection_on_plane(s.b, window_width, window_height));
        }
    }

    window.draw(figure);
}

void Solid3d::rotate_around_vector(const Vector3d rotation_center, const Vector3d &axis, const double theta) {
    
    for (auto &s : edges) {
        s.a.rotate(rotation_center, axis, theta);
        s.b.rotate(rotation_center, axis, theta);
    }

    center.rotate(rotation_center, axis, theta);
}

void Solid3d::rotate(const Vector3d &axis, const double theta) {
    rotate_around_vector(center, axis, theta);
}
