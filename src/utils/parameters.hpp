#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <iomanip>
#include <numeric>
#include "timer.hpp"

#define INITIAL_WINDOW_WIDTH  1900
#define INITIAL_WINDOW_HEIGHT 1200

#define RED        "\033[0;31m"
#define GREEN      "\033[0;32m"
#define ORANGE     "\033[0;33m"
#define LIGHT_GRAY "\033[0;37m"
#define NO_COLOR   "\033[0m"

class Parameters {
public:
    static int window_width;
    static int window_height;
    static std::vector<double> cpu_usage;
    static Timer print_cpu_usage_timer;

public:
    static void update_window_size(const int width, const int height) { window_width  = width;
                                                                        window_height = height; }
    static void print_mean_CPU_usage(std::ostream& os, const double current_loop_time, const double allowed_loop_time);
};

#endif
