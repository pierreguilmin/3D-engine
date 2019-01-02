#ifndef SOLID3D_FIELD_HPP
#define SOLID3D_FIELD_HPP

#include "utils/tools.hpp"
#include "geometry/vector3d.hpp"
#include "geometry/geometry.hpp"

// https://stackoverflow.com/questions/43200852/template-arguments-in-constructor-of-non-template-class
template <class T>
struct SolidType {};

class Solid3dField {
private:
    std::vector<Solid3d> solids;
    std::vector<Vector3d> rotation_axes;
    std::vector<double> rotation_speeds;

public:
    // constructors
    template <typename T>
    Solid3dField(SolidType<T>,
                 const Vector3d &center,
                 const unsigned density,
                 const int radius);

    // others
    void render(sf::RenderWindow &window,
                const unsigned window_width,
                const unsigned window_height,
                const Camera3d &camera) const;
    void move();
};

// ##############################################
// ### constructors #############################
// ##############################################

// only Solid3d defined by center and size
template <typename T>
Solid3dField::Solid3dField(SolidType<T>,
                           const Vector3d &center,
                           const unsigned density,
                           const int radius) {

    for (unsigned i = 0; i < density; ++i) {
        Vector3d offset(rand(-radius, radius), rand(-radius, radius), rand(-radius, radius));
        solids.push_back(T(center + offset, rand(10, 50)));

        rotation_axes.push_back(Vector3d(rand(0.0, 1.0), rand(0.0, 1.0), rand(0.0, 1.0)));
        rotation_speeds.push_back(rand(-5.0, 5.0));
    }
}

#endif
