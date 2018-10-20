#include "parameters.hpp"

unsigned Parameters::window_width  = INITIAL_WINDOW_WIDTH;
unsigned Parameters::window_height = INITIAL_WINDOW_HEIGHT;
std::vector<double> Parameters::cpu_usage;
LoopTimer Parameters::print_CPU_usage_timer(sf::seconds(1));


void Parameters::update_window_size(const unsigned width, const unsigned height) {
    window_width  = width;
    window_height = height;
}

void Parameters::print_mean_CPU_usage(std::ostream &os, const double main_loop_duration) {

    cpu_usage.push_back(main_loop_duration / MAX_MAIN_LOOP_DURATION);

    if (print_CPU_usage_timer.is_done()) {

        // compute mean_cpu_usage
        double mean_cpu_usage = 0.0;

        for (auto x : cpu_usage)
            mean_cpu_usage += x;

        mean_cpu_usage /= cpu_usage.size();

        // print mean_cpu_usage
        os << std::setprecision(1) << std::fixed;
        os << LIGHT_GREY << "CPU usage (last 1s): ";
        if (mean_cpu_usage <= 0.5)
            os << GREEN;
        else if (mean_cpu_usage >= 0.9)
            os << RED;
        else
            os << ORANGE;

        os << 100 * mean_cpu_usage << "%" << NO_COLOR << std::endl;


        cpu_usage.clear();
    }
}

