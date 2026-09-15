#include "Game.h"
#include "Player.h"

namespace AGSnake2D::Game
{
	bool m_is_playing = true;
	bool m_is_visible = true;
	bool m_is_first_pass = true;
	float m_refresh_rate;
	float m_time_elapsed = 0;

	unsigned int m_tile_size;
	unsigned int m_rows;
	unsigned int m_columns;
	sf::Vector2f m_position;

	DIRECTION m_direction;

	sf::RectangleShape m_background;
}

void AGSnake2D::Game::init(unsigned int tile_size, unsigned int rows, unsigned int columns, sf::Vector2f position, float refresh_rate)
{
	m_tile_size = tile_size;
	m_rows = rows;
	m_columns = columns;

	m_refresh_rate = refresh_rate;
	
	m_background = sf::RectangleShape(sf::Vector2f(m_rows * m_tile_size, m_columns * m_tile_size));
	m_background.setFillColor(sf::Color::Black);
	m_background.setOutlineColor(sf::Color::White);
	m_background.setOutlineThickness(2.0f);

	set_position(position);

	AGSnake2D::Player::init(m_tile_size);
	AGSnake2D::Player::set_position(sf::Vector2f(m_position.x + 10 * m_tile_size, m_position.y + 10 * m_tile_size));
}

void AGSnake2D::Game::update(float dt)
{
	m_time_elapsed += dt;

	if (m_time_elapsed >= m_refresh_rate)
	{
		m_time_elapsed = 0;

		if (!m_is_playing)
			return;

		switch (m_direction)
		{
		case DIRECTION::UP:
			Player::set_position(sf::Vector2f(Player::get_position().x, Player::get_position().y - m_tile_size));
			break;

		case DIRECTION::DOWN:
			Player::set_position(sf::Vector2f(Player::get_position().x, Player::get_position().y + m_tile_size));
			break;

		case DIRECTION::LEFT:
			Player::set_position(sf::Vector2f(Player::get_position().x - m_tile_size, Player::get_position().y));
			break;

		case DIRECTION::RIGHT:
			Player::set_position(sf::Vector2f(Player::get_position().x + m_tile_size, Player::get_position().y));
			break;
		}
	}
}

void AGSnake2D::Game::render(sf::RenderWindow& window)
{
	window.draw(m_background);
	Player::render(window);
}

void AGSnake2D::Game::set_is_playing(bool val)
{
	m_is_playing = val;
}

void AGSnake2D::Game::set_is_visible(bool val)
{
	m_is_visible = val;
}

void AGSnake2D::Game::set_position(sf::Vector2f new_pos)
{
	m_position = new_pos;
	m_background.setPosition(m_position);
}

void AGSnake2D::Game::set_player_direction(DIRECTION _direction) 
{
	switch (_direction)
	{
	case DIRECTION::UP:
		if (m_direction != DIRECTION::DOWN)
			m_direction = DIRECTION::UP;
		break;

	case DIRECTION::DOWN:
		if (m_direction != DIRECTION::UP)
			m_direction = DIRECTION::DOWN;
		break;

	case DIRECTION::LEFT:
		if (m_direction != DIRECTION::RIGHT)
			m_direction = DIRECTION::LEFT;
		break;

	case DIRECTION::RIGHT:
		if (m_direction != DIRECTION::LEFT)
			m_direction = DIRECTION::RIGHT;
		break;
	}
}