#include "geometry.hpp"

// ##############################################
// ## Segment3d #################################
// ##############################################

Segment3d& Segment3d::operator=(const Segment3d &s) {

	if (this != &s) {
		a = s.a;
		b = s.b;
	}

	return *this;
}



// ##############################################
// ## Plane3d ###################################
// ##############################################

Plane3d& Plane3d::operator=(const Plane3d &p) {
	if (this != &p) {
		base   = p.base;
		normal = p.normal;
	}

	return *this;
}

// p(x, y, z) in plane [n(a, b, c), b] ⟺ n . (p - b)        = 0
// 				                       ⟺ n.p - n.b          = 0
//                                     ⟺ ax + by + cz - n.b = 0 ⟹ d = - n.b
double Plane3d::get_equation_value_of_d() const {
	return - (normal * base);
}

// v(x, y, z) point and p plane [n, b] with n unit vector, v2 normal intersection of v with p, distance:
// D = | n . (v - v2) |
//   = | n.v - n.v2 |
//   = | n.v - d | because d = - n.v2
// if p[N, b], D = | n.v - d | * 1 / | n |
// removing the | | of the nominator yields the "signed distance", eg:
//    - the distance D
//    - the sign being > 0 if the point is "above the normal side", < 0 if "under the normal side"
double Plane3d::signed_distance_from_point_to_plane(const Vector3d &v) const {
	return v * normal + get_equation_value_of_d() / normal.norm();
}

// #TODO: missing comment
bool Plane3d::handle_intersection_segment_with_plane(Segment3d &s) const {
	double da = signed_distance_from_point_to_plane(s.a);
	double db = signed_distance_from_point_to_plane(s.b);

	if (da < 0 && db < 0)
		return true;
	else if (da > 0 & db < 0) {
		double f = da / (da - db); // intersection factor (between 0 and 1)
		sf::Color new_color = s.b.color = sf::Color(s.a.color.r + f * (s.b.color.r - s.a.color.r),
											        s.a.color.g + f * (s.b.color.g - s.a.color.g),
											        s.a.color.b + f * (s.b.color.b - s.a.color.b));
		s.b = s.a + (s.b - s.a) * f;

		s.b.color = new_color;
	}
	else if (da < 0 & db > 0) {
		std::swap(s.a, s.b);
		handle_intersection_segment_with_plane(s);
	}

	return false;
}

// #TODO: explain change point opacity
sf::Vertex Plane3d::get_point_projection_on_plane(Vector3d &v) const {
	sf::Color vertex_color = v.color;

	vertex_color.a = map(signed_distance_from_point_to_plane(v), 0, PROJECTION_MAX_DEPTH, 255, 0); 

	return sf::Vertex(sf::Vector2f(PROJECTION_FACTOR * v.x / v.z + Parameters::window_width  / 2,
								   PROJECTION_FACTOR * v.y / v.z + Parameters::window_height / 2),
	                  vertex_color);
}



// ##############################################
// ## Camera3d #################################
// ##############################################

// #TODO: explain frustrum creation
Camera3d::Camera3d(const Vector3d _position,
	               const double _theta_x,
	               const double _theta_y,
	               const double _theta_z) : position(_position),
							    			theta_x(as_radian(_theta_x)),
							    			theta_y(as_radian(_theta_y)),
							    			theta_z(as_radian(_theta_z)) {

	const double horizontal_angle = atan2(Parameters::window_width  / 2.0, PROJECTION_FACTOR) - 0.0001;
	const double vertical_angle   = atan2(Parameters::window_height / 2.0, PROJECTION_FACTOR) - 0.0001;
	const double ch = cos(horizontal_angle);
	const double sh = sin(horizontal_angle);
	const double cv = cos(vertical_angle);
	const double sv = sin(vertical_angle);

	frustrum[0] = Plane3d(Vector3d(0, 0, 0                   ), Vector3d(0  , 0  , 1 )); // close
	frustrum[1] = Plane3d(Vector3d(0, 0, PROJECTION_MAX_DEPTH), Vector3d(0  , 0  , -1)); // far
	frustrum[2] = Plane3d(Vector3d(0, 0, 0                   ), Vector3d(ch , 0  , sh)); // left
	frustrum[3] = Plane3d(Vector3d(0, 0, 0                   ), Vector3d(-ch, 0  , sh)); // right
	frustrum[4] = Plane3d(Vector3d(0, 0, 0                   ), Vector3d(0  , cv , sv)); // top
	frustrum[5] = Plane3d(Vector3d(0, 0, 0                   ), Vector3d(0  , -cv, sv)); // bottom
}

void Camera3d::reload_frustrum() {
	*this = Camera3d(position, as_degree(theta_x), as_degree(theta_y), as_degree(theta_z));
}

void Camera3d::rotate(const double mouse_move_x, const double mouse_move_y) {
	theta_x -= as_radian(mouse_move_y) * CAMERA_ROTATION_SENSIBILITY;
	theta_y += as_radian(mouse_move_x) * CAMERA_ROTATION_SENSIBILITY;
}

// #TODO: missing comment
void Camera3d::move(const DIRECTION direction) {
	Vector3d normal(cos(theta_x) * sin(theta_y), - sin(theta_x), cos(theta_x) * cos(theta_y));
	normal = normal.get_normalized();

	Vector3d orthog(normal.z, 0, - normal.x);
	orthog = orthog.get_normalized();

	Vector3d up(0, 1, 0);

	if (direction == DIRECTION::FRONT) 
    	translate(normal);
    else if (direction == DIRECTION::BEHIND)
    	translate(- normal);
    else if (direction == DIRECTION::RIGHT)
    	translate(orthog);
    else if (direction == DIRECTION::LEFT)
    	translate(- orthog);
    else if (direction == DIRECTION::UP)
    	translate(up);
    else if (direction == DIRECTION::DOWN)
    	translate(- up);
}

// #TODO: missing comment
Vector3d Camera3d::transform_point(const Vector3d &v) const {
	Vector3d new_v(v);

	double cx = cos(theta_x), cy = cos(theta_y), cz = cos(theta_z);
	double sx = sin(theta_x), sy = sin(theta_y), sz = sin(theta_z);
	Vector3d u = v - position; // camera as the center of the world in (0, 0, 0)

	double x = u.x, y = u.y, z = u.z;

	// rotations
	return (Vector3d(cy * (sz * y + cz * x) - sy * z,
					 sx * (cy * z + sy * (sz * y + cz * x)) + cx * (cz * y - sz * x),
					 cx * (cy * z + sy * (sz * y + cz * x)) - sx * (cz * y - sz * x), v.color));
}

Segment3d Camera3d::transform_segment(const Segment3d &s) const {
 	return Segment3d(transform_point(s.a), transform_point(s.b));
}



// ##############################################
// ## Solid3d ###################################
// ##############################################

Solid3d Solid3d::operator+=(const Solid3d &solid) {
	for (auto seg : solid.edges)
		this -> add_segment(seg);

	center = (solid.center + center) * 0.5;

	return *this;
}

Solid3d Solid3d::operator+(const Vector3d &v) const {
	Solid3d new_solid(*this);

	for (auto &seg : new_solid.edges) {
		seg.a += v;
		seg.b += v;
	}

	new_solid.center += v;

	return new_solid;
}

Solid3d Solid3d::operator+=(const Vector3d &v) {
	for (auto &seg : edges) {
		seg.a += v;
		seg.b += v;
	}

	center += v;

	return *this;
}


// #TODO: missing comment
Solid3d::Solid3d(const SOLID_TYPE type, const string &parameters_string) {
	figure.setPrimitiveType(sf::Lines);

	vector<string> parameters = parse_string(parameters_string, ':');

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

    			points.push_back(Vector3d(size * cos(as_radian(theta)) * cos(as_radian(phi)),
		    							  size * cos(as_radian(theta)) * sin(as_radian(phi)),
		    							  size * sin(as_radian(theta))));
    		}
    	}

    	for (size_t i = 0; i < points.size(); ++i)
    		add_segment(Segment3d(points[i], points[i] + Vector3d(0.5, 0, 0)));
	}
}

void Solid3d::set_center(const Vector3d &_center) {
	*this += _center;

	center = _center;
}

// #TODO: missing comment
void Solid3d::render_solid(sf::RenderWindow &window, const Camera3d &camera) {
	figure.clear();

	for (auto s : edges) {
		bool outside_frustrum = false;
		s = camera.transform_segment(s);

		for (auto side : camera.frustrum) {
			outside_frustrum = side.handle_intersection_segment_with_plane(s);
			if (outside_frustrum)
				break;
		}

		if (! outside_frustrum) {
			figure.append(camera.frustrum[0].get_point_projection_on_plane(s.a));
			figure.append(camera.frustrum[0].get_point_projection_on_plane(s.b));
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
