#include "Player.h"

AGSnake2D::Player::Player(unsigned int tile_size, unsigned int rows, unsigned int columns) : Sprite(tile_size)
{
	m_tail_coords.reserve(rows * columns);
	m_shape.setFillColor(sf::Color::Green);
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

void AGSnake2D::Player::add_tail(sf::Vector2f coords)
{
	m_tail_coords.push_back(coords);
}
