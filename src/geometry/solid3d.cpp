#include "solid3d.hpp"

// ##############################################
// ### operators ################################
// ##############################################

// Solid3d Solid3d::operator+=(const Solid3d &solid) {
//     for (auto s : solid.edges)
//         this -> add_segment(s);

//     return *this;
// }

Solid3d Solid3d::operator+(const Vector3d &v) const {
    Solid3d new_solid(*this);

    new_solid += v;

    return new_solid;
}

Solid3d Solid3d::operator+=(const Vector3d &v) {
    for (auto &p : points)
        p += v;

    center += v;

    return *this;
}


// ##############################################
// ### others ###################################
// ##############################################

void Solid3d::get_max_size() {
    for (auto p : points)
        max_size = std::max({max_size, (p - center).norm()});
}

// #TODO: missing comment
void Solid3d::render_solid(sf::RenderWindow &window,
                           const unsigned window_width,
                           const unsigned window_height,
                           const Camera3d &camera) {

    figure.clear();

    bool inside_frustrum = true;

    // check if center is too far from frustrum
    if (max_size >= 0) {
        const Vector3d temp_center = camera.transform_vector(center);

        for (auto side : camera.frustrum) {
            double d = side.get_signed_distance_from_point_to_plane(temp_center);

            // further than max_size in the opposite direction from one frustrum plane
            if (d <= - max_size)
                return;
            // within every frustrum plane in the good direction by at least max_size
            else if (d <= max_size) {
                inside_frustrum = false;
                break;
            }
        }
    }


    std::vector<Vector3d> points_tr(points);
    for (auto &p : points_tr)
        p = camera.transform_vector(p);

    for (auto s : edges) {
        bool outside_frustrum = false;

        if (! inside_frustrum) {
            for (auto side : camera.frustrum) {
                outside_frustrum = side.handle_intersection_of_segment_with_plane(s.get_a(points_tr),
                                                                                  s.get_b(points_tr));
                if (outside_frustrum)
                    break;
            }
        }

        if (! outside_frustrum) {
            figure.append(camera.frustrum[0].get_projection_on_plane(s.get_a(points_tr),
                                                                     window_width,
                                                                     window_height));
            figure.append(camera.frustrum[0].get_projection_on_plane(s.get_b(points_tr),
                                                                     window_width, 
                                                                     window_height));
        }
    }

    window.draw(figure);
}

void Solid3d::rotate_around_vector(const Vector3d rotation_center,
                                   const Vector3d &axis,
                                   const double theta) {
    
    for (auto &p : points)
        p.rotate(rotation_center, axis, theta);

    center.rotate(rotation_center, axis, theta);
}

void Solid3d::rotate(const Vector3d &axis, const double theta) {
    rotate_around_vector(center, axis, theta);
}
