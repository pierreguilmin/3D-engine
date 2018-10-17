#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "../utils/general.hpp"
#include <iomanip> // for std::setprecision and std::setw

class Vector3d {
private:
	double x, y, z;
	sf::Color color;

public:
	// constructors
	Vector3d() : x(0.0), y(0.0), z(0.0), color(sf::Color::White) {}
	Vector3d(const double _x, const double _y, const double _z) : x(_x), y(_y), z(_z), color(sf::Color::White) {}
	Vector3d(const double _x, const double _y, const double _z, const sf::Color _color) : x(_x), y(_y), z(_z), color(_color) {}
	Vector3d(const Vector3d &v) : x(v.x), y(v.y), z(v.z), color(v.color) {}
	Vector3d(const Vector3d &v, const sf::Color _color) : x(v.x), y(v.y), z(v.z), color(_color) {}

	// operators
	Vector3d& operator=(const Vector3d &v);
	Vector3d operator+(const Vector3d &v) const;
	Vector3d operator+=(const Vector3d &v);
	Vector3d operator-(const Vector3d &v) const;
	Vector3d operator-=(const Vector3d &v);
	Vector3d operator-();
	Vector3d operator*(const double factor) const;
	Vector3d operator*=(const double factor);
	double operator*(const Vector3d &v) const;

	// other
	double norm() const { return sqrt(x * x + y * y + z * z); }
	Vector3d get_normalized() const;
	double distance_to(const Vector3d &v) const;
	void rotate(const Vector3d &center, const Vector3d &axis, const double theta);


friend std::ostream& operator<<(std::ostream& os, const Vector3d &v);
friend class Segment3d;
friend class Plane3d;
friend class Solid3d;
friend class Camera3d;
};

#endif
