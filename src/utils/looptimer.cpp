#include "looptimer.hpp"

bool LoopTimer::is_done() {
    if (getElapsedTime() >= time) {
        this -> restart();

        return true;
    }
    
    return false;
}
