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
protected:
    std::vector<Vector3d> points;
    const unsigned nb_circles, nb_points_per_circle;

public:
    Sphere3d(const Vector3d &_center, 
             const double size,
             const unsigned _nb_circles,
             const unsigned _nb_points_per_circle,
             const bool add_latitude_segments=true,
             const bool add_longitude_segments=false);

protected:
    void _add_segments(const bool add_latitude_segments, const bool add_longitude_segments);
};


// ##############################################
// ### Asteroid3d ###############################
// ##############################################

class Asteroid3d : public Sphere3d {

public:
    Asteroid3d(const Vector3d &_center, 
               const double size);
};

#endif
