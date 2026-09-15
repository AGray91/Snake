#include "Game_Over_Menu.h"

namespace AGSnake2D::Game_Over_Menu
{
	bool m_is_visible;
	sf::Font m_font;
	sf::RectangleShape m_background;
}

void AGSnake2D::Game_Over_Menu::init(sf::RenderWindow& window)
{
	assert(m_font.openFromFile(FONT));
	m_is_visible = true;
	m_background.setSize(sf::Vector2f(window.getSize()));
}

void AGSnake2D::Game_Over_Menu::render(sf::RenderWindow& window)
{
	m_background.setFillColor(BACKGROUND_COLOUR);
	window.draw(m_background);

	sf::Text m_txt_title(m_font);
	m_txt_title.setString(GAME_OVER_MESSAGE);
	m_txt_title.setCharacterSize(TITLE_CHARSIZE);
	m_txt_title.setFillColor(FONT_COLOUR);
	sf::Vector2f title_bounds = m_txt_title.getLocalBounds().size;
	m_txt_title.setPosition((sf::Vector2f((window.getSize().x - title_bounds.x) / 2, (window.getSize().y - title_bounds.y - 100) / 2)));
	window.draw(m_txt_title);
}

void AGSnake2D::Game_Over_Menu::set_is_visible(bool val)
{
	m_is_visible = val;
}

bool AGSnake2D::Game_Over_Menu::get_is_visible()
{
	return m_is_visible;
}
