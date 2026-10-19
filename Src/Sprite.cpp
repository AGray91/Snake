#include "Sprite.h"

AGSnake2D::Sprite::Sprite(unsigned int tile_size)
{
	m_shape.setSize(sf::Vector2f(tile_size, tile_size));
}

void AGSnake2D::Sprite::set_position(sf::Vector2f new_pos)
{
	m_position = new_pos;
}

sf::Vector2f AGSnake2D::Sprite::get_position()
{
	return m_position;
}

sf::Vector2f AGSnake2D::Sprite::get_size()
{
	return m_shape.getSize();
}

void AGSnake2D::Sprite::render(sf::RenderWindow& window)
{
	m_shape.setPosition(m_position);
	window.draw(m_shape);
}