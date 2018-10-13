#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>

class Timer : public sf::Clock {
private:
    sf::Time time;

public:
    Timer(const sf::Time &_time) : time(_time) { Clock(); }

    bool is_done();
};

#endif
