#include "solid3d.hpp"

// ##############################################
// ### constructors #############################
// ##############################################

// #TODO: missing comment
Solid3d::Solid3d(const SOLID_TYPE type, const std::string &parameters_string) {
    figure.setPrimitiveType(sf::Lines);

    std::vector<std::string> parameters = parse_string(parameters_string, ':');

    double size = std::stoi(parameters[0]);

    if (type == SOLID_TYPE::CUBE) {
        Vector3d points[8];

        // front
        points[0] = Vector3d(size / 2, size / 2, size / 2);
        points[1] = points[0] + Vector3d(size, 0   , 0);
        points[2] = points[0] + Vector3d(size, size, 0);
        points[3] = points[0] + Vector3d(0   , size, 0);

        // back
        for (int i = 4; i < 8; ++i)
            points[i] = points [i - 4] + Vector3d(0, 0, size);

        for (int i = 0; i < 8; ++i)
            points[i].color = get_random_colour();

        for (int i = 0; i < 4; ++i) {
            add_segment(Segment3d(points[i], points[(i + 1) % 4]));         // front face
            add_segment(Segment3d(points[i + 4], points[(i + 1) % 4 + 4])); // back face
            add_segment(Segment3d(points[i], points[i + 4]));               // links
        }
    }
    else if (type == SOLID_TYPE::SPHERE) {
        unsigned number_of_circles = std::stoi(parameters[1]);
        unsigned number_of_points_per_circle = std::stoi(parameters[2]);

        std::vector<Vector3d> points;

        for (unsigned i = 0; i < number_of_circles; ++i) {
            double theta = map(i, 0, number_of_circles - 1, -90, 90);

            for (unsigned j = 0; j < number_of_points_per_circle; ++j) {
                double phi = map(j, 0, number_of_points_per_circle, -180, 180);

                points.push_back(Vector3d(size * cos(as_radians(theta)) * cos(as_radians(phi)),
                                          size * cos(as_radians(theta)) * sin(as_radians(phi)),
                                          size * sin(as_radians(theta))));
            }
        }

        for (size_t i = 0; i < points.size(); ++i)
            add_segment(Segment3d(points[i], points[i] + Vector3d(0.5, 0, 0)));
    }
}


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

void Solid3d::set_center(const Vector3d &_center) {
    *this += _center;
    center = _center;
}

// #TODO: missing comment
void Solid3d::render_solid(sf::RenderWindow &window, const unsigned window_width, const unsigned window_height, const Camera3d &camera) {
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

void Solid3d::rotate(const Vector3d &rotation_center, const Vector3d &axis, const double theta, const bool object_axis) {
    
    Vector3d center_of_rotation(rotation_center);

    if (object_axis) 
        center_of_rotation = center;

    for (auto &s : edges) {
        s.a.rotate(center_of_rotation, axis, theta);
        s.b.rotate(center_of_rotation, axis, theta);
    }
}
