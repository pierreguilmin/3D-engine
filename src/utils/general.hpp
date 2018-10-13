#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "parameters.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

double square(const double x);
double map(const double x, const double a, const double b, const double c, const double d);
double as_radian(const double theta);
double as_degree(const double theta);

vector<string> parse_string(const string &string_to_parse, const char sep);

int rand(const int a, const int b);
double rand(const double a, const double b);
sf::Color get_random_colour();

#endif
