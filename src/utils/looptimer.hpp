#ifndef LOOPTIMER_HPP
#define LOOPTIMER_HPP

#include <SFML/Graphics.hpp>

class LoopTimer : public sf::Clock {
private:
    sf::Time time;

public:
    LoopTimer(const sf::Time &_time) : time(_time) { Clock(); }

    bool is_done();
};

#endif
