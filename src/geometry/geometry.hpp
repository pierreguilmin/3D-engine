#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "../utils/tools.hpp"
#include "vector3d.hpp"
#include "segment3d.hpp"
#include "solid3d.hpp"

// ##############################################
// ### Cube3d ###################################
// ##############################################

class Cube3d : public Solid3d {

public:
    Cube3d(const Vector3d &_center, const double size);
};


// ##############################################
// ### Sphere3d #################################
// ##############################################

class Sphere3d : public Solid3d {

public:
    Sphere3d(const Vector3d &_center, 
             const double size,
             const unsigned number_of_circles,
             const unsigned number_of_points_per_circle);
};


// ##############################################
// ### Asteroid3d ###############################
// ##############################################

class Asteroid3d : public Solid3d {

public:
    Asteroid3d(const Vector3d &_center, const double size);
};

#endif
