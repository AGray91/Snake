#pragma once
#include <SFML/Graphics.hpp>

namespace AGSnake2D
{
	enum DIRECTION
	{
		UP = 0,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};

	namespace Game
	{
		void init(unsigned int tile_size, unsigned int rows, unsigned int columns, sf::Vector2f position, float refresh_rate);
		void update(float dt);
		void render(sf::RenderWindow& window);

		void set_is_playing(bool val);
		void set_is_visible(bool val);
		void set_position(sf::Vector2f new_pos);
		void set_player_direction(DIRECTION _direction);
	}
}