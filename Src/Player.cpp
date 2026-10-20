#include "Player.h"

AGSnake2D::Player::Player(unsigned int tile_size, unsigned int rows, unsigned int columns) : Sprite(tile_size)
{
	m_tail_coords.reserve(rows * columns);
	set_colour(sf::Color::Green);
}

void AGSnake2D::Player::update_tail()
{
	if (m_tail_coords.size() < 1)
		return;

	for (size_t i = m_tail_coords.size() - 1; i > 0; i--)
	{
		m_tail_coords[i] = m_tail_coords[i--];
	}

	m_tail_coords[0] = m_position;
}

void AGSnake2D::Player::render(sf::RenderWindow& window)
{
	m_shape.setPosition(m_position);
	window.draw(m_shape);

	if (m_tail_coords.size() < 1)
		return;

	for (size_t i = 0; i < m_tail_coords.size(); i++)
	{
		sf::RectangleShape tail_shape(m_tail_coords[i]);
		window.draw(tail_shape);
	}
}

void AGSnake2D::Player::add_tail(DIRECTION direction)
{
	sf::Vector2f last_coords;

	if (m_tail_coords.size() > 1)
		last_coords = m_tail_coords[m_tail_coords.size() - 1];
	else
		last_coords = m_position;

	sf::Vector2f new_tail_coords;

	switch (direction)
	{
	case DIRECTION::LEFT:
		new_tail_coords = sf::Vector2f(last_coords.x + m_tile_size, last_coords.y);
		break;

	case DIRECTION::RIGHT:
		new_tail_coords = sf::Vector2f(last_coords.x - m_tile_size, last_coords.y);
		break;

	case DIRECTION::UP:
		new_tail_coords = sf::Vector2f(last_coords.x, last_coords.y + m_tile_size);
		break;

	case DIRECTION::DOWN:
		new_tail_coords = sf::Vector2f(last_coords.x, last_coords.y - m_tile_size);
		break;
	}

	m_tail_coords.push_back(new_tail_coords);
}
