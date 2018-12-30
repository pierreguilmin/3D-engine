#include "segment3d.hpp"

// ##############################################
// ### operators ################################
// ##############################################

Segment3d& Segment3d::operator=(const Segment3d &s) {
    if (this != &s) {
        i = s.i;
        j = s.j;
    }

    return *this;
}
