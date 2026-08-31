#include "Game.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define TITLE			"SNAKE"
#define FRAMERATELIMIT	60

#define TILE_SIZE		32
#define ROWS			10
#define COLUMNS			10

// INPUT MAP
#define ESCAPE			sf::Keyboard::Key::Escape
#define UP				sf::Keyboard::Key::W
#define DOWN			sf::Keyboard::Key::S
#define LEFT			sf::Keyboard::Key::A
#define RIGHT			sf::Keyboard::Key::D

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

void AGSnake2D::run_game()
{
	// Create Window...
	m_window.create(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), TITLE, sf::Style::Default);
	m_window.setFramerateLimit(FRAMERATELIMIT);

	m_fps = 0.0f;

	// Main Loop...
	while (m_window.isOpen())
	{
		m_dt = m_clock.restart();
		m_fps = m_dt.asSeconds();

		input();
		update(m_fps);
		render();
	}
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
			case ESCAPE:
				m_window.close();
				break;

			case UP:
				break;

			case DOWN:
				break;

			case LEFT:
				break;

			case RIGHT:
				break;
			}
		}
	}
}

void AGSnake2D::update(float _fps)
{

}

void AGSnake2D::render()
{
	m_window.clear();
	m_window.display();
}