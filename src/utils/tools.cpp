#include "tools.hpp"

// return the square number of x
double square(const double x) {
	return x * x;
}

// return the math modulo of x (and not the C++ modulo, wrong for negative numbers)
// -2 % 10 ⟹ -2 instead of 8
int mod(const int a, const int b) {
	if (a >=0)
		return a % b;
	else
		return a % b + b;
 }

// if x < a ⟹ c, if x > b ⟹ d
double constrain(const double x, const double a, const double b) {
 	if (x < a)
		return a;
	else if (x > b)
		return b;
	
	return x;
 }

// map linearly x from [a, b] to [c, d], if x < a ⟹ c, if x > b ⟹ d
double map(const double x, const double a, const double b, const double c, const double d) {
	const double x_c = constrain(x, a, b);

	return (x_c - a) / (b - a) * (d - c) + c;
}

// https://en.wikipedia.org/wiki/Gaussian_function#Two-dimensional_Gaussian_function
double map_gaussian_2d(const double x, const double x_a, const double x_b,
                       const double y, const double y_a, const double y_b,
                       const double amplitude) {
	const double mu_x = 0.0, mu_y = 0.0, sigma_x = 1.0, sigma_y = 1.0;

	const double x_mapped = map(x, x_a, x_b, - 3 * sigma_x, 3 * sigma_x);
	const double y_mapped = map(y, y_a, y_b, - 3 * sigma_y, 3 * sigma_y);

	return amplitude * exp(- (square(x_mapped - mu_x) / 2 * square(sigma_x) +
	                          square(y_mapped - mu_y) / 2 * square(sigma_y)));
}

// convert theta in degrees to radian
double as_radians(const double theta) {
	return theta / 180.0 * M_PI;
}

// convert theta in radian to degrees
double as_degrees(const double theta) {
	return theta / M_PI * 180.0;
}

// returns a random integer between [a, b[
int rand(const int a, const int b) {
	return rand() % (b - a) + a;
}

// returns a random double between [a, b[
double rand(const double a, const double b) {
	return rand() / static_cast<double>(RAND_MAX) * (b - a) + a;
}

// returns a sf::Color object having random rgb values (ie a random colour)
sf::Color get_random_colour(const int r_min, const int r_max,
                            const int g_min, const int g_max,
                            const int b_min, const int b_max) {
	return sf::Color(rand(r_min, r_max + 1),
	                 rand(g_min, g_max + 1),
	                 rand(b_min, b_max + 1));
}
