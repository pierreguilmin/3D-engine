#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "general.hpp"


class Mouse : public sf::Mouse {
private:
	static unsigned last_position_x, last_position_y;

public:
	static int get_move_x(const sf::RenderWindow &window);
	static int get_move_y(const sf::RenderWindow &window);

	static void setPosition(const sf::Vector2i &position, const sf::Window &relativeTo);
};

#endif

