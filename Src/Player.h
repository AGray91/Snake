#pragma once
#include <SFML/Graphics.hpp>

namespace AGSnake2D::Player
{
	void init(unsigned int tile_size);
	void render(sf::RenderWindow& window);

	void set_position(sf::Vector2f pos);
	sf::Vector2f get_position();
}