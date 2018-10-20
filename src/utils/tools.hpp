#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

double square(const double x);
double map(const double x, const double a, const double b, const double c, const double d);
double as_radian(const double theta);
double as_degree(const double theta);

std::vector<std::string> parse_string(const std::string &string_to_parse, const char sep);

int rand(const int a, const int b);
double rand(const double a, const double b);
sf::Color get_random_colour();

#endif
