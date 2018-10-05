#include "general.hpp"

// return the square number of x
double square(const double x) {
	return x * x;
}

// map linearly x from [a, b] to [c, d], if x < a ⟹ c, if x > b ⟹ s
double map(double x, const double a, const double b, const double c, const double d) {
	if (x < a)
		x = a;
	else if (x > b)
		x = b;

	return (x - a) / (b - a) * (d - c) + c;
}

// convert theta in degrees to radian
double as_radian(const double theta) {
	return theta / 180.0 * M_PI;
}

// convert theta in radian to degrees
double as_degree(const double theta) {
	return theta / M_PI * 180.0;
}

// split string by sep and returns a vector of string
// ex: parse_string_to_int("12:40:3", ':') ⟹ std::vector<int> [12, 40, 3]
vector<string> parse_string(const string &string_to_parse, const char sep)
{
	vector<string> sub_strings;
	string temp;

	for (auto c : string_to_parse)
	{
		if (c == sep)
		{
			sub_strings.push_back(temp);
			temp = "";
		}
		else
			temp += c;
	}

	sub_strings.push_back(temp);

	return sub_strings;
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
sf::Color get_random_colour() {
	return sf::Color(rand(0, 256), rand(0, 256), rand(0, 256));
}



// ##############################################
// ## Timer #####################################
// ##############################################

bool Timer::is_done() {
	if (getElapsedTime() >= time) {
		this -> restart();

		return true;
	}
	
	return false;
}



// ##############################################
// ## Parameters ###############################
// ##############################################

int Parameters::window_width  = INITIAL_WINDOW_WIDTH;
int Parameters::window_height = INITIAL_WINDOW_HEIGHT;
std::vector<double> Parameters::cpu_usage;
Timer Parameters::print_cpu_usage_timer(sf::seconds(1));

void Parameters::print_mean_CPU_usage(std::ostream& os, const double current_loop_time, const double allowed_loop_time) {

	cpu_usage.push_back(current_loop_time / allowed_loop_time);

	if (print_cpu_usage_timer.is_done()) {

		double mean_cpu_usage = std::accumulate(cpu_usage.begin(), cpu_usage.end(), 0.0) / cpu_usage.size() * 100;

	    os << std::setprecision(2) << std::fixed << std::setw(3);
	    os << LIGHT_GRAY << "CPU usage (1s): ";
	    if (mean_cpu_usage <= 50)
	        os << GREEN;
	    else if (mean_cpu_usage >= 90)
	        os << RED;
	    else
	        os << ORANGE;

	    os << mean_cpu_usage << "%" << NO_COLOR << endl;

	    cpu_usage.clear();
	}
}

