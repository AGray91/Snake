#include "Game.h"

AGSnake2D::Game::Game(unsigned int tile_size, unsigned int rows, unsigned int columns, float refresh_rate)
{
	m_tile_size = tile_size;
	m_rows = rows;
	m_columns = columns;

	m_refresh_rate = refresh_rate;
	
	m_background = sf::RectangleShape(sf::Vector2f(m_rows * m_tile_size, m_columns * m_tile_size));
	m_background.setFillColor(sf::Color::Black);
	m_background.setOutlineColor(sf::Color::White);
	m_background.setOutlineThickness(2.0f);

	m_is_playing = false;
	m_is_visible = true;
	m_is_first_pass = true;
	m_time_elapsed = 0.0f;

	m_direction = DIRECTION::UP;
}

void AGSnake2D::Game::restart()
{
	m_player.reset();
	m_player = std::make_unique<Player>(m_tile_size, m_rows, m_columns);
	m_player->set_position(sf::Vector2f(m_position.x + 10 * m_tile_size, m_position.y + 10 * m_tile_size));

	set_is_playing(true);
}

void AGSnake2D::Game::input(const sf::Event& event)
{
	if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		switch (keyPressed->code)
		{
		case K_UP:
			Game::set_player_direction(DIRECTION::UP);
			break;

		case K_DOWN:
			Game::set_player_direction(DIRECTION::DOWN);
			break;

		case K_LEFT:
			Game::set_player_direction(DIRECTION::LEFT);
			break;

		case K_RIGHT:
			Game::set_player_direction(DIRECTION::RIGHT);
			break;
		}
	}
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
			m_player->set_position(sf::Vector2f(m_player->get_position().x, m_player->get_position().y - m_tile_size));
			break;

		case DIRECTION::DOWN:
			m_player->set_position(sf::Vector2f(m_player->get_position().x, m_player->get_position().y + m_tile_size));
			break;

		case DIRECTION::LEFT:
			m_player->set_position(sf::Vector2f(m_player->get_position().x - m_tile_size, m_player->get_position().y));
			break;

		case DIRECTION::RIGHT:
			m_player->set_position(sf::Vector2f(m_player->get_position().x + m_tile_size, m_player->get_position().y));
			break;
		}

		m_player->update_tail();
		check_bounds();	// Check if Player has gone out of bounds...
	}
}

void AGSnake2D::Game::render(sf::RenderWindow& window)
{
	if (!m_is_visible)
		return;

	window.draw(m_background);
	m_player->render(window);
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

void AGSnake2D::Game::bind_game_over(std::function<void()> delegate)
{
	m_delegate_game_over = delegate;
}

void AGSnake2D::Game::check_bounds()
{
	sf::Vector2f bg_pos = m_background.getPosition();
	sf::Vector2f bg_size = bg_pos + m_background.getSize();

	sf::Vector2f p_pos = m_player->get_position();
	sf::Vector2f p_size = p_pos + m_player->get_size();

	if (p_pos.x < bg_pos.x || p_pos.y < bg_pos.y || p_size.x > bg_size.x || p_size.y > bg_size.y)
	{
		m_is_playing = false;

		if (m_delegate_game_over)
			m_delegate_game_over();
	}
}