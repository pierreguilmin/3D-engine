#include "geometry.hpp"

// ##############################################
// ### Cube3d ###################################
// ##############################################

Cube3d::Cube3d(const Vector3d &_center, const double size) : Solid3d() {
    Vector3d base_point = Vector3d(-size / 2, -size / 2, -size / 2);

    // front
    add_point(base_point);
    add_point(base_point + Vector3d(size, 0   , 0));
    add_point(base_point + Vector3d(size, size, 0));
    add_point(base_point + Vector3d(0   , size, 0));

    // back
    for (auto p : points)
        add_point(p + Vector3d(0, 0, size));

    for (auto &p : points)
        p.set_color(get_random_colour());

    for (int i = 0; i < 4; ++i) {
        add_segment(i    , (i + 1) % 4);     // front face
        add_segment(i + 4, (i + 1) % 4 + 4); // back face
        add_segment(i    , i + 4);           // links
    }

    *this += _center;

    set_max_size(size * sqrt(3));
}


// ##############################################
// ### Ellipsoid3d ##############################
// ##############################################

Ellipsoid3d::Ellipsoid3d(const Vector3d &_center, 
                         const double a, const double b, const double c,
                         const unsigned _nb_circles,
                         const unsigned _nb_points_per_circle,
                         const bool add_latitude_segments,
                         const bool add_longitude_segments) : Solid3d(),
                                                              nb_circles(_nb_circles),
                                                              nb_points_per_circle(_nb_points_per_circle)
                                                              {

    for (int i = 0; i < nb_circles; ++i) {
        double theta = map(i, 0, nb_circles - 1, -88, 88);

        for (int j = 0; j < nb_points_per_circle; ++j) {
            double phi = map(j, 0, nb_points_per_circle, -180, 180);

            add_point(Vector3d(a * cos(as_radians(theta)) * cos(as_radians(phi)),
                               b * cos(as_radians(theta)) * sin(as_radians(phi)),
                               c * sin(as_radians(theta))));
        }
    }

    _add_segments(add_latitude_segments, add_longitude_segments);

    *this += _center;

    set_max_size(std::max({a, b, c}));
}

void Ellipsoid3d::_add_segments(const bool add_latitude_segments, const bool add_longitude_segments) {
    for (int i = 0; i < nb_circles; ++i) {
        for (int j = 0; j < nb_points_per_circle; ++j) {

            if (add_latitude_segments)
                add_segment(_index_point_at(i, j), _index_point_at(i, j - 1));

            if (add_longitude_segments && i > 0)
                add_segment(_index_point_at(i, j), _index_point_at(i - 1, j));
        }
    }
}

size_t Ellipsoid3d::_index_point_at(const size_t circle_idx, const size_t point_idx) {
    return mod(circle_idx, nb_circles) * nb_points_per_circle + mod(point_idx, nb_points_per_circle);
}

// // ##############################################
// // ### Asteroid3d ###############################
// // ##############################################

Asteroid3d::Asteroid3d(const Vector3d &_center,
                       const double size,
                       const unsigned asteroid_complexity) : Ellipsoid3d(_center,
                                                                         size, size, size * rand(1.0, 2.5),
                                                                         20, 20,
                                                                         false, false) {

    *this += -Vector3d(_center);

    for (int i = 0; i < nb_circles; ++i) {
        for (int j = 0; j < nb_points_per_circle; ++j) {

            points[_index_point_at(i, j)].set_color(get_random_colour(110, 160,
                                                                      60, 110,
                                                                      20, 80));

            if (i > 4 && i < nb_circles - 4 && rand(0, asteroid_complexity) == 0) {

                const double amplitude = rand(0.1, 0.2) * (rand(0, 2) * 2 - 1);
                const int radius = rand(4.0, nb_points_per_circle / 4.0), sub_radius = rand(3.0, nb_circles / 6.0);

                for (int k = - radius; k <= radius; ++k) {
                    for (int l = - sub_radius; l <= sub_radius; ++l) {
                        const double factor = 1.0 + map_gaussian_2d(k, -radius, radius,
                                                                    l, -sub_radius, sub_radius,
                                                                    amplitude);
                        if (i + l >= 0 && i + l < nb_circles)
                            points[_index_point_at(i + l, j + k)] *= factor;
                    }
                }
            }
        }
    }

    _add_segments(true, true);

    *this += _center;

    get_max_size();
}
