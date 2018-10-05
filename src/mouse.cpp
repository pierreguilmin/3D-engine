#include "mouse.hpp"

unsigned Mouse::last_position_x = 0;
unsigned Mouse::last_position_y = 0;

int Mouse::get_move_x(const sf::RenderWindow &window) {
	int move_x = getPosition(window).x - last_position_x;
	last_position_x = getPosition(window).x;

	return move_x;
}

int Mouse::get_move_y(const sf::RenderWindow &window) {
	int move_y = getPosition(window).y - last_position_y;
	last_position_y = getPosition(window).y;

	return move_y;
}

// extend sf::Mouse inherited function
void Mouse::setPosition(const sf::Vector2i &position, const sf::Window &relativeTo) {
	sf::Mouse::setPosition(position, relativeTo);

	last_position_x = position.x;
	last_position_y = position.y;
}
