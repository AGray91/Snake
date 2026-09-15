#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#define MAX_STRING_LEN 32
#define FONT "..\\..\\..\\Assets\\Fonts\\KOMIKAP_.ttf"
#define FONT_COLOUR sf::Color::White

#define TITLE "Snake 2D"
#define TITLE_CHARSIZE 75

#define PLAY "Play"
#define PLAY_CHARSIZE 45
#define PLAY_HIGHLIGHT sf::Color(211, 211, 211, 255)
#define PLAY_BTN_WIDTH 160
#define PLAY_BTN_HEIGHT 80

namespace AGSnake2D::Main_Menu
{
	void init(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);

	void set_is_visible(bool val);
	bool get_is_visible();
}