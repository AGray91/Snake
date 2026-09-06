#include "Player.h"

namespace AGSnake2D::Player
{
	bool initialised = false;
	sf::Vector2f m_position;
	sf::RectangleShape m_shape;
}

void AGSnake2D::Player::init(unsigned int tile_size)
{
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setSize(sf::Vector2f(tile_size, tile_size));
}

void AGSnake2D::Player::render(sf::RenderWindow& window)
{
	m_shape.setPosition(m_position);
	window.draw(m_shape);
}

void AGSnake2D::Player::set_position(sf::Vector2f pos)
{
	m_position = pos;
}

sf::Vector2f AGSnake2D::Player::get_position()
{
	sf::Vector2f retVal = sf::Vector2f(0, 0);

	retVal = m_position;

	return retVal;
}