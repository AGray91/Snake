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

// INPUT MAP
#define K_ESCAPE		sf::Keyboard::Key::Escape
#define K_UP			sf::Keyboard::Key::W
#define K_DOWN			sf::Keyboard::Key::S
#define K_LEFT			sf::Keyboard::Key::A
#define K_RIGHT			sf::Keyboard::Key::D

namespace AGSnake2D
{
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Time m_dt;

	float m_fps;

	void input();
	void update(float _dt);
	void render();
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
	AGSnake2D::Game::set_is_visible(false);
	AGSnake2D::Game::set_is_playing(false);

	// Set up Main Menu UI...
	AGSnake2D::Main_Menu::init(AGSnake2D::m_window);

	// Set up Game Over UI...
	AGSnake2D::Game_Over_Menu::init(AGSnake2D::m_window);
	

	// Main loop...
	while (AGSnake2D::m_window.isOpen())
	{
		AGSnake2D::m_dt = AGSnake2D::m_clock.restart();
		AGSnake2D::m_fps = AGSnake2D::m_dt.asSeconds();

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
		else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			switch (keyPressed->code)
			{
			case K_ESCAPE:
				m_window.close();
				break;

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
}

void AGSnake2D::update(float _fps)
{
	Main_Menu::update(m_window);
	Game::update(_fps);
}

void AGSnake2D::render()
{
	m_window.clear();

	
	Main_Menu::render(m_window);
	Game::render(m_window);
	Game_Over_Menu::render(m_window);

	m_window.display();
}