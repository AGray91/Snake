#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#define FONT				"..\\..\\..\\Assets\\Fonts\\KOMIKAP_.ttf"
#define FONT_COLOUR			sf::Color::White
#define GAME_OVER_MESSAGE	"GAME OVER"
#define TITLE_CHARSIZE		75
#define BACKGROUND_COLOUR	sf::Color::Black

namespace AGSnake2D::Game_Over_Menu
{
	void init(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	void set_is_visible(bool val);
	bool get_is_visible();
}