#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "plane3d.hpp"

#define CAMERA_ROTATION_SENSIBILITY 0.25
#define CAMERA_TRANSLATION_SENSIBILITY 4

class Camera3d {
public:
	enum class DIRECTION {FRONT, BEHIND, RIGHT, LEFT, UP, DOWN};

private:
	Vector3d position;
	double theta_x, theta_y, theta_z;

	Plane3d frustrum[6];

public:
	Camera3d(const Vector3d _position,
		     const double _theta_x,
		     const double _theta_y,
		     const double _theta_z);

	void reload_frustrum();
	void rotate(const double mouse_move_x, const double mouse_move_y);
	void move(const DIRECTION direction);

	Vector3d transform_point(const Vector3d &v) const;
	Segment3d transform_segment(const Segment3d &s) const;

private:
	void translate(const Vector3d &v) { position = (position + v * CAMERA_TRANSLATION_SENSIBILITY); }

friend class Solid3d;
};



#endif
