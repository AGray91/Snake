#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Main_Menu.h"
#include "Game_Over_Menu.h"

#define SCREEN_WIDTH	1200
#define SCREEN_HEIGHT	800
#define TITLE			"SNAKE"
#define FRAMERATE_LIMIT	60
#define REFRESH_RATE	0.2

#define TILE_SIZE		32
#define ROWS			21
#define COLUMNS			21

namespace AGSnake2D
{
	enum EState
	{
		MAIN_MENU = 0,
		GAME = 1,
		END_MENU = 2
	};

	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Time m_dt;

	float m_fps;
	EState m_state;

	bool m_timer_active;
	float m_timer_time;
	float m_timer_target;

	void input();
	void update(float _dt);
	void render();

	void start_game();
	void end_game();

	void start_timer();
	void update_timer(float elasped);
}

int main()
{
	// Create Window...
	AGSnake2D::m_window.create(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), TITLE, sf::Style::Default);
	AGSnake2D::m_window.setFramerateLimit(FRAMERATE_LIMIT);
	
	// Set up game layout and initialise game...
	 sf::Vector2f game_pos = sf::Vector2f((SCREEN_WIDTH - ROWS * TILE_SIZE) / 2, (SCREEN_HEIGHT - COLUMNS * TILE_SIZE) / 2);
	AGSnake2D::Game::init(TILE_SIZE, ROWS, COLUMNS, game_pos, REFRESH_RATE);

	// DEBUG...
	AGSnake2D::Game::set_is_playing(false);
	AGSnake2D::Game::bind_game_over(AGSnake2D::end_game);

	// Set up Main Menu UI...
	AGSnake2D::Main_Menu::init(AGSnake2D::m_window);
	AGSnake2D::Main_Menu::bind_play_btn_onclick(AGSnake2D::start_game);

	// Set up Game Over UI...
	 AGSnake2D::Game_Over_Menu::init(AGSnake2D::m_window);

	 // Set initial state...
	 AGSnake2D::m_state = AGSnake2D::EState::MAIN_MENU;

	 // Set up time management...
	 AGSnake2D::m_timer_active = false;
	 AGSnake2D::m_timer_time = 0;
	 AGSnake2D::m_timer_target = 5.0f;
	

	// Main loop...
	while (AGSnake2D::m_window.isOpen())
	{
		AGSnake2D::m_dt = AGSnake2D::m_clock.restart();
		AGSnake2D::m_fps = AGSnake2D::m_dt.asSeconds();

		if (AGSnake2D::m_timer_active)
			AGSnake2D::update_timer(AGSnake2D::m_fps);

		AGSnake2D::input();
		AGSnake2D::update(AGSnake2D::m_fps);
		AGSnake2D::render();
	}

	return 0;
}

void AGSnake2D::input()
{
	while (std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}
		else
		{
			switch (m_state)
			{
			case MAIN_MENU:
				AGSnake2D::Main_Menu::handle_event(*event);
				break;

			case GAME:
				AGSnake2D::Game::handle_event(*event);
				break;

			case END_MENU:
				AGSnake2D::Game_Over_Menu::handle_event(*event);
				break;
			}
		}
	}
}

void AGSnake2D::update(float _fps)
{
	switch (m_state)
	{
	case MAIN_MENU:
		AGSnake2D::Main_Menu::update(m_window);
		break;

	case GAME:
		AGSnake2D::Game::update(_fps);
		break;

	case END_MENU:
		break;
	}
}

void AGSnake2D::render()
{
	m_window.clear();

	
	switch (m_state)
	{
	case MAIN_MENU:
		AGSnake2D::Main_Menu::render(m_window);
		break;

	case GAME:
		AGSnake2D::Game::render(m_window);
		break;

	case END_MENU:
		AGSnake2D::Game_Over_Menu::render(m_window);
		break;
	}

	m_window.display();
}

void AGSnake2D::start_game()
{
	m_state = EState::GAME;
	Game::set_is_playing(true);
}

void AGSnake2D::end_game()
{
	m_state = EState::END_MENU;
	start_timer();
}

void AGSnake2D::start_timer()
{
	m_timer_active = true;
	m_timer_time = 0.0;
}

void AGSnake2D::update_timer(float elapsed)
{
	m_timer_time += elapsed;

	if (m_timer_time > m_timer_target)
	{
		m_timer_time = 0.0f;
		m_timer_active = false;
		m_state = EState::MAIN_MENU;
	}
}