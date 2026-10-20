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

	m_apple_caught = false;

	m_direction = DIRECTION::UP;

	m_random_gen = std::make_unique<Random_Gen>();
}

void AGSnake2D::Game::restart()
{
	// Spawn new Player...
	m_player.reset();
	m_player = std::make_unique<Player>(m_tile_size, m_rows, m_columns);
	// Place Player at the center of the game world...
	m_player->set_position(sf::Vector2f(m_position.x + (m_rows / 2) * m_tile_size, m_position.y + (m_columns / 2) * m_tile_size));

	// Spawn new Apple...
	m_apple.reset();
	m_apple = std::make_unique<Sprite>(m_tile_size);
	m_apple->set_colour(sf::Color::Red);

	float rand_x = m_random_gen->range(0, m_rows) * m_tile_size;
	float rand_y = m_random_gen->range(0, m_columns) * m_tile_size;
	m_apple->set_position(sf::Vector2f(m_position.x + rand_x, m_position.y + rand_y));

	// Set game playing...
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
		if (m_apple_caught)
			next_apple();

		m_player->update_tail();

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

		
		check_bounds();	// Check if Player has gone out of bounds...

		m_apple_caught = is_apple_caught();
	}
}

void AGSnake2D::Game::render(sf::RenderWindow& window)
{
	if (!m_is_visible)
		return;

	window.draw(m_background);
	m_player->render(window);
	m_apple->render(window);
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

bool AGSnake2D::Game::is_apple_caught()
{
	bool retval = false;

	unsigned int player_row = (m_player->get_position().x / m_tile_size) - m_position.x;
	unsigned int player_col = (m_player->get_position().y / m_tile_size) - m_position.y;

	unsigned int apple_row = (m_apple->get_position().x / m_tile_size) - m_position.x;
	unsigned int apple_col = (m_apple->get_position().y / m_tile_size) - m_position.y;

	if (player_row == apple_row && player_col == apple_col)
		retval = true;

	return retval;
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

void AGSnake2D::Game::next_apple()
{
	m_apple.reset();
	m_apple = std::make_unique<Sprite>(m_tile_size);
	m_apple->set_colour(sf::Color::Red);

	float rand_x = m_random_gen->range(0, m_rows) * m_tile_size;
	float rand_y = m_random_gen->range(0, m_columns) * m_tile_size;
	m_apple->set_position(sf::Vector2f(m_position.x + rand_x, m_position.y + rand_y));

	m_player->add_tail(m_direction);
}