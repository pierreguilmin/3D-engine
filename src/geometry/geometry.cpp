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

    //for (int i = 0; i < 8; ++i)
    //    points[i].color = get_random_colour();

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
                   const unsigned number_of_circles,
                   const unsigned number_of_points_per_circle) : Solid3d() {

    std::vector<Vector3d> points;

    for (unsigned i = 0; i < number_of_circles; ++i) {
        double theta = map(i, 0, number_of_circles - 1, -90, 90);

        for (unsigned j = 0; j < number_of_points_per_circle; ++j) {
            double phi = map(j, 0, number_of_points_per_circle, -180, 180);

            points.push_back(Vector3d(size * cos(as_radians(theta)) * cos(as_radians(phi)),
                                      size * cos(as_radians(theta)) * sin(as_radians(phi)),
                                      size * sin(as_radians(theta))));

            // no need to repeat this point
            if (theta == -90 || theta == 90)
                break;
        }
    }

    for (size_t i = 0; i < points.size(); ++i)
        add_segment(Segment3d(points[i], points[i] + Vector3d(0.5, 0, 0)));

    *this += _center;
}
