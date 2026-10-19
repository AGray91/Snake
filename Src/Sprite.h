#pragma once
#include <SFML/Graphics.hpp>

namespace AGSnake2D
{
	class Sprite
	{
	public:
		Sprite(unsigned int tile_size);

		virtual void render(sf::RenderWindow& window);

		void set_position(sf::Vector2f new_pos);
		sf::Vector2f get_position();
		sf::Vector2f get_size();

	protected:
		sf::RectangleShape m_shape;
		sf::Vector2f m_position;
	};
}