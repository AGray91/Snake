#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Player.h"

// INPUT MAP
#define K_ESCAPE		sf::Keyboard::Key::Escape
#define K_UP			sf::Keyboard::Key::W
#define K_DOWN			sf::Keyboard::Key::S
#define K_LEFT			sf::Keyboard::Key::A
#define K_RIGHT			sf::Keyboard::Key::D

namespace AGSnake2D
{
	enum DIRECTION
	{
		UP = 0,
		DOWN = 2,
		LEFT = 4,
		RIGHT = 8
	};

	class Game
	{
	public:
		Game(unsigned int tile_size, unsigned int rows, unsigned int columns, float refresh_rate);

		void input(const sf::Event& event);
		void update(float dt);
		void render(sf::RenderWindow& window);
		void restart();
		void set_is_playing(bool val);
		void set_is_visible(bool val);
		void set_position(sf::Vector2f new_pos);

		void bind_game_over(std::function<void()> call_back);

	private:
		// Properties...
		bool m_is_playing;
		bool m_is_visible;
		bool m_is_first_pass;
		float m_refresh_rate;
		float m_time_elapsed;

		unsigned int m_tile_size;
		unsigned int m_rows;
		unsigned int m_columns;
		sf::Vector2f m_position;

		DIRECTION m_direction;

		sf::RectangleShape m_background;

		std::function<void()> m_delegate_game_over;

		std::unique_ptr<Player> m_player;

		// Methods...
		void check_bounds();
		void set_player_direction(DIRECTION _direction);
	};
}