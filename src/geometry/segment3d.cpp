#include "segment3d.hpp"

Segment3d& Segment3d::operator=(const Segment3d &s) {
    if (this != &s) {
        a = s.a;
        b = s.b;
    }

    return *this;
}
