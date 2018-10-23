#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

double square(const double x);
int mod(const int a, const int b);

double constrain(const double x, const double a, const double b);
double map(const double x, const double a, const double b, const double c, const double d);
double map_gaussian_2d(const double x, const double x_a, const double x_b,
                       const double y, const double y_a, const double y_b,
                       const double amplitude);

double as_radians(const double theta);
double as_degrees(const double theta);
int rand(const int a, const int b);
double rand(const double a, const double b);
sf::Color get_random_colour(const int r_min = 0, const int r_max = 255,
                            const int g_min = 0, const int g_max = 255,
                            const int b_min = 0, const int b_max = 255);

#endif
