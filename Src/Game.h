#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

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

	namespace Game
	{
		void init(unsigned int tile_size, unsigned int rows, unsigned int columns, sf::Vector2f position, float refresh_rate);
		void handle_event(const sf::Event& event);
		void update(float dt);
		void render(sf::RenderWindow& window);

		void set_is_playing(bool val);
		void set_is_visible(bool val);
		void set_position(sf::Vector2f new_pos);
		void set_player_direction(DIRECTION _direction);

		void bind_game_over(std::function<void()> delegate);
	}
}