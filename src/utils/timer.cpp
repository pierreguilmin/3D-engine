#include "timer.hpp"

bool Timer::is_done() {
    if (getElapsedTime() >= time) {
        this -> restart();

        return true;
    }
    
    return false;
}
