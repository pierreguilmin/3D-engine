#include "parameters.hpp"

int Parameters::window_width  = INITIAL_WINDOW_WIDTH;
int Parameters::window_height = INITIAL_WINDOW_HEIGHT;
std::vector<double> Parameters::cpu_usage;
LoopTimer Parameters::print_CPU_usage_timer(sf::seconds(1));

void Parameters::print_mean_CPU_usage(std::ostream& os, const double current_loop_time, const double allowed_loop_time) {

    cpu_usage.push_back(current_loop_time / allowed_loop_time);

    if (print_CPU_usage_timer.is_done()) {

        double mean_cpu_usage = std::accumulate(cpu_usage.begin(), cpu_usage.end(), 0.0) / cpu_usage.size() * 100;

        os << std::setprecision(2) << std::fixed << std::setw(3);
        os << LIGHT_GREY << "CPU usage (1s): ";
        if (mean_cpu_usage <= 50)
            os << GREEN;
        else if (mean_cpu_usage >= 90)
            os << RED;
        else
            os << ORANGE;

        os << mean_cpu_usage << "%" << NO_COLOR << std::endl;

        cpu_usage.clear();
    }
}

