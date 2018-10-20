#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include <iomanip> // for std::setprecision
#include "looptimer.hpp"

#define INITIAL_WINDOW_WIDTH  1900
#define INITIAL_WINDOW_HEIGHT 1200

#define FPS 60
#define MAX_MAIN_LOOP_DURATION (1000.0 / FPS)

#define RED        "\033[31m"
#define GREEN      "\033[32m"
#define ORANGE     "\033[33m"
#define LIGHT_GREY "\033[37m"
#define NO_COLOR   "\033[0m"

class Parameters {
public:
    static unsigned window_width;
    static unsigned window_height;
    static std::vector<double> cpu_usage;
    static LoopTimer print_CPU_usage_timer;

public:
    static void update_window_size(const unsigned width, const unsigned height);
    static void print_mean_CPU_usage(std::ostream &os, const double main_loop_duration);
};

#endif
