#include "looptimer.hpp"

bool LoopTimer::is_done() {
    if (getElapsedTime() >= loop_time) {
        this -> restart();

        return true;
    }
    
    return false;
}
