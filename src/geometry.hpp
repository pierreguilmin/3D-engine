#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "general.hpp"
#include "vector3d.hpp"

#define PROJECTION_FACTOR 1024.0
#define PROJECTION_MAX_DEPTH 800

#define CAMERA_ROTATION_SENSIBILITY 0.25
#define CAMERA_TRANSLATION_SENSIBILITY 4


// ##############################################
// ## Segment3d #################################
// ##############################################

class Segment3d {
private:
	Vector3d a, b;

public:
	Segment3d() : a(Vector3d()), b(Vector3d()) {}
	Segment3d(const Vector3d &_a, const Vector3d &_b) : a(_a), b(_b) {}
	Segment3d(const Vector3d &_a, const Vector3d &_b, const sf::Color _color) : a(_a), b(_b) { a.color = _color;
																							   b.color = _color; }
	Segment3d(const Segment3d &s) : a(s.a), b(s.b) {}

	Segment3d& operator=(const Segment3d &s);

friend class Plane3d;
friend class Camera3d;
friend class Solid3d;
};



// ##############################################
// ## Plane3d ###################################
// ##############################################

class Plane3d {
private:
	Vector3d base;
	Vector3d normal;
	
public:
	Plane3d() : base(Vector3d()), normal(Vector3d()) {}
	Plane3d(const Vector3d &_base, const Vector3d &_normal) : base(_base), normal(_normal) {}
	Plane3d(const Plane3d &p) : base(p.base), normal(p.normal) {}

	Plane3d& operator=(const Plane3d &p);

	double get_equation_value_of_d() const;
	double signed_distance_from_point_to_plane(const Vector3d &v) const;
	bool handle_intersection_segment_with_plane(Segment3d &s) const;
	sf::Vertex get_point_projection_on_plane(Vector3d &v) const;
};



// ##############################################
// ## Camera3d ##################################
// ##############################################

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



// ##############################################
// ## Solid3d ###################################
// ##############################################

class Solid3d {
public:
	enum class SOLID_TYPE {CUBE, SPHERE};

public:
	std::vector<Segment3d> edges;
	sf::VertexArray figure;
	Vector3d center;

public:
	Solid3d() { figure.setPrimitiveType(sf::Lines); }
	Solid3d(const SOLID_TYPE type, const string &parameters_string);

	Solid3d operator+=(const Solid3d &solid);
	Solid3d operator+(const Vector3d &v) const;
	Solid3d operator+=(const Vector3d &v);

	void set_center(const Vector3d &_center);
	void add_segment(const Segment3d &s) { edges.push_back(s); }
	void render_solid(sf::RenderWindow &window, const Camera3d &camera);
	void clear() { edges.clear(); }
	void rotate(const Vector3d &rotation_center, const Vector3d &axis, const double theta, const bool object_axis = false);

};


#endif
