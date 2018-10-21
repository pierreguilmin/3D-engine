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
// ### Ellipsoid3d ##############################
// ##############################################
class Ellipsoid3d : public Solid3d {
protected:
    std::vector<Vector3d> points;
    const unsigned nb_circles, nb_points_per_circle;

public:
    Ellipsoid3d(const Vector3d &_center, 
                const double a, const double b, const double c,
                const unsigned _nb_circles,
                const unsigned _nb_points_per_circle,
                const bool add_latitude_segments=true,
                const bool add_longitude_segments=false);

protected:
    void _add_segments(const bool add_latitude_segments, const bool add_longitude_segments);
    Vector3d& _point_at(const size_t circle_idx, const size_t point_idx);
};


// ##############################################
// ### Sphere3d #################################
// ##############################################

class Sphere3d : public Ellipsoid3d {
public:
    Sphere3d(const Vector3d &_center, 
             const double size,
             const unsigned _nb_circles,
             const unsigned _nb_points_per_circle,
             const bool add_latitude_segments=true,
             const bool add_longitude_segments=false) : Ellipsoid3d(_center,
                                                                    size, size, size,
                                                                    _nb_circles,
                                                                    _nb_points_per_circle,
                                                                    add_latitude_segments,
                                                                    add_longitude_segments) {}
};


// ##############################################
// ### Asteroid3d ###############################
// ##############################################

class Asteroid3d : public Ellipsoid3d {

public:
    Asteroid3d(const Vector3d &_center, 
               const double size);
};

#endif
