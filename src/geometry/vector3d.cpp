#include "vector3d.hpp"

// ##############################################
// ## operators  ################################
// ##############################################

Vector3d& Vector3d::operator=(const Vector3d &v) {
	if (this != &v) {
		x = v.x;
		y = v.y;
		z = v.z;
		color = v.color;
	}

	return *this;
}

Vector3d Vector3d::operator+(const Vector3d &v) const {
	return Vector3d(x + v.x, y + v.y, z + v.z, color);
}

Vector3d Vector3d::operator+=(const Vector3d &v) {
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector3d Vector3d::operator-(const Vector3d &v) const {
	return Vector3d(x - v.x, y - v.y, z - v.z, color);
}

Vector3d Vector3d::operator-=(const Vector3d &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector3d Vector3d::operator-() {
	x = - x;
	y = - y;
	z = - z;

	return *this;
}

Vector3d Vector3d::operator*(const double factor) const {
	return Vector3d(x * factor, y * factor, z * factor, color);
}

Vector3d Vector3d::operator*=(const double factor) {
	x *= factor;
	y *= factor;
	z *= factor;

	return *this;
}

double Vector3d::operator*(const Vector3d &v) const {
	return x * v.x + y * v.y + z * v.z;
}

std::ostream& operator<<(std::ostream& os, const Vector3d &v) {
	os << std::setprecision(2) << std::fixed;

	os << "x: "    << std::setw(6) << v.x;
	os << " | y: " << std::setw(6) << v.y;
	os << " | z: " << std::setw(6) << v.z;

	os << std::endl;

	return os;
}


// ##############################################
// ## other #####################################
// ##############################################

Vector3d Vector3d::get_normalized() const {
	return (*this) * (1 / this->norm());
}

double Vector3d::distance_to(const Vector3d &v) const {
	return ((*this) - v).norm();
}

// See https://en.wikipedia.org/wiki/Rotation_matrix#In_three_dimensions part "Rotation matrix from axis and angle"
void Vector3d::rotate(const Vector3d &center, const Vector3d &axis, const double theta) {
	Vector3d temp(*this);

	*this -= center;

	Vector3d ax = axis.get_normalized();
	double ux = ax.x, uy = ax.y, uz = ax.z;
	double c = cos(as_radian(theta)), s = sin(as_radian(theta));

	temp.x = x * (c + square(ux) * (1 - c))   + y * (ux * uy * (1 - c) - uz * s) + z * (ux * uz * (1 - c) + uy * s);
	temp.y = x * (uy * ux * (1 - c) + uz * s) + y * (c + square(uy) * (1 - c))   + z * (uy * uz * (1 - c) - ux * s);
	temp.z = x * (uz * ux * (1 - c) - uy * s) + y * (uz * uy * (1 - c) + ux * s) + z * (c + square(uz) * (1 - c));

	*this = temp + center;
}
