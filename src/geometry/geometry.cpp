#include "geometry.hpp"

// ##############################################
// ### Cube3d ###################################
// ##############################################

Cube3d::Cube3d(const Vector3d &_center, const double size) : Solid3d() {
    Vector3d points[8];

    // front
    points[0] = Vector3d(-size / 2, -size / 2, -size / 2);
    points[1] = points[0] + Vector3d(size, 0   , 0);
    points[2] = points[0] + Vector3d(size, size, 0);
    points[3] = points[0] + Vector3d(0   , size, 0);

    // back
    for (int i = 4; i < 8; ++i)
        points[i] = points [i - 4] + Vector3d(0, 0, size);

    for (int i = 0; i < 8; ++i)
        points[i].set_color(get_random_colour());

    for (int i = 0; i < 4; ++i) {
        add_segment(Segment3d(points[i], points[(i + 1) % 4]));         // front face
        add_segment(Segment3d(points[i + 4], points[(i + 1) % 4 + 4])); // back face
        add_segment(Segment3d(points[i], points[i + 4]));               // links
    }

    *this += _center;
}


// ##############################################
// ### Sphere3d #################################
// ##############################################

Sphere3d::Sphere3d(const Vector3d &_center, 
                   const double size,
                   const unsigned _nb_circles,
                   const unsigned _nb_points_per_circle,
                   const bool add_latitude_segments,
                   const bool add_longitude_segments) : Solid3d(),
                                                        nb_circles(_nb_circles),
                                                        nb_points_per_circle(_nb_points_per_circle) {

    for (unsigned i = 0; i < nb_circles; ++i) {
        double theta = map(i, 0, nb_circles - 1, -88, 88);

        for (unsigned j = 0; j < nb_points_per_circle; ++j) {
            double phi = map(j, 0, nb_points_per_circle, -180, 180);

            points.push_back(Vector3d(size * cos(as_radians(theta)) * cos(as_radians(phi)),
                                      size * cos(as_radians(theta)) * sin(as_radians(phi)),
                                      size * sin(as_radians(theta))));
        }
    }

    _add_segments(add_latitude_segments, add_longitude_segments);

    *this += _center;
}

void Sphere3d::_add_segments(const bool add_latitude_segments, const bool add_longitude_segments) {
    for (unsigned i = 0; i < nb_circles; ++i) {
        for (unsigned j = 0; j < nb_points_per_circle; ++j) {
            size_t current_point_idx = i * nb_points_per_circle + j;

            if (add_latitude_segments) {
                if (j > 0)
                    add_segment(Segment3d(points[current_point_idx],
                                          points[current_point_idx - 1]));
                else
                    add_segment(Segment3d(points[current_point_idx],
                                          points[current_point_idx + nb_points_per_circle - 1]));
            }

            if (add_longitude_segments && i > 0)
                add_segment(Segment3d(points[current_point_idx],
                                      points[current_point_idx - nb_points_per_circle]));
        }
    }
}


// ##############################################
// ### Asteroid3d ###############################
// ##############################################

Asteroid3d::Asteroid3d(const Vector3d &_center, const double size) : Sphere3d(_center,
                                                                              size,
                                                                              30,
                                                                              50,
                                                                              false,
                                                                              false) {

    *this += -Vector3d(_center);

    bool make_asteroid = true;

    for (unsigned i = 0; i < nb_circles; ++i) {

        for (unsigned j = 0; j < nb_points_per_circle; ++j) {
            size_t current_point_idx = i * nb_points_per_circle + j;

            double deformation_factor = map(i, 0, nb_circles -1, -size, size);
            points[current_point_idx] += Vector3d(0, 0, deformation_factor);
            points[current_point_idx].set_color(sf::Color(rand(170, 220),
                                                          rand(100, 150),
                                                          rand(30, 80)));

            if (make_asteroid &&
                i >= 2 && i < nb_circles - 2 &&
                j >= 2 && j < nb_points_per_circle - 2 &&
                rand(0, 10) == 0) {

                const double factor = rand(1.0, 1.3);
                const size_t radius = rand(10, 20);

                for (size_t k = 1; k < radius; ++k) {
                    const double sub_factor = map(k, 0, radius - 1, factor, 1);

                    points[current_point_idx - k] *= sub_factor;
                    points[current_point_idx + k] *= sub_factor;

                    for (size_t l = 1; l < static_cast<size_t>(radius / 2); ++l) {
                        const double sub_sub_factor = map(l, 0, static_cast<size_t>(radius / 2), sub_factor, 1);

                        points[current_point_idx - k + nb_points_per_circle * l] *= sub_sub_factor;
                        points[current_point_idx + k + nb_points_per_circle * l] *= sub_sub_factor;
                    }
                }

                points[current_point_idx - nb_points_per_circle] *= (1 + factor) / 2;
                points[current_point_idx + nb_points_per_circle] *= (1 + factor) / 2;
                points[current_point_idx] *= factor;
            }
        }
    }

    _add_segments(true, true);

    *this += _center;
}

