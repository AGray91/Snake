#pragma once
#include "Sprite.h"
#include <memory>

namespace AGSnake2D
{
	class Player : public Sprite
	{
	public:
		Player(unsigned int tile_size, unsigned int rows, unsigned int columns);

		void update_tail();
		void render(sf::RenderWindow& window) override;
		void add_tail(sf::Vector2f coords);

	protected:
		std::vector<sf::Vector2f> m_tail_coords;
	};
}