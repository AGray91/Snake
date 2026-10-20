#pragma once
#include "Sprite.h"
#include <memory>

namespace AGSnake2D
{
	enum DIRECTION
	{
		UP = 0,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};

	class Player : public Sprite
	{
	public:
		Player(unsigned int tile_size, unsigned int rows, unsigned int columns);

		void update_tail();
		void render(sf::RenderWindow& window) override;
		void add_tail(DIRECTION direction);

	protected:
		std::vector<sf::Vector2f> m_tail_coords;
	};
}