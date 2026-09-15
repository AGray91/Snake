#include "Main_Menu.h"

namespace AGSnake2D::Main_Menu
{
	sf::Font m_font;
	sf::RectangleShape m_play_btn;

	bool m_is_visible = false;

	void render_title(sf::RenderWindow& window);
	void render_play(sf::RenderWindow& window);
}

void AGSnake2D::Main_Menu::init(sf::RenderWindow& window)
{
	assert(m_font.openFromFile(FONT));

	m_play_btn.setFillColor(sf::Color::Black);
	m_play_btn.setOutlineColor(FONT_COLOUR);
	m_play_btn.setOutlineThickness(2);
	m_play_btn.setSize(sf::Vector2f(PLAY_BTN_WIDTH, PLAY_BTN_HEIGHT));
	m_play_btn.setPosition(sf::Vector2f((window.getSize().x - PLAY_BTN_WIDTH) / 2 , 400));

	m_is_visible = true;
}

void AGSnake2D::Main_Menu::render(sf::RenderWindow& window)
{	
	if (!m_is_visible)
		return;

	render_title(window);
	render_play(window);
}

void AGSnake2D::Main_Menu::update(sf::RenderWindow& window)
{
	if (!m_is_visible)
		return;

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_pos_2f = sf::Vector2f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));

	if (m_play_btn.getGlobalBounds().contains(mouse_pos_2f))
		m_play_btn.setFillColor(PLAY_HIGHLIGHT);
	else
		m_play_btn.setFillColor(sf::Color::Black);
}

void AGSnake2D::Main_Menu::render_title(sf::RenderWindow& window)
{
	sf::Text m_txt_title(m_font);
	m_txt_title.setString(TITLE);
	m_txt_title.setCharacterSize(TITLE_CHARSIZE);
	m_txt_title.setFillColor(FONT_COLOUR);
	sf::Vector2f title_bounds = m_txt_title.getLocalBounds().size;
	m_txt_title.setPosition((sf::Vector2f((window.getSize().x - title_bounds.x) / 2, 100)));
	window.draw(m_txt_title);
}

void AGSnake2D::Main_Menu::render_play(sf::RenderWindow& window)
{
	sf::Text m_txt_play(m_font);
	m_txt_play.setString(PLAY);
	m_txt_play.setCharacterSize(PLAY_CHARSIZE);
	m_txt_play.setFillColor(FONT_COLOUR);
	sf::Vector2f play_bounds = m_txt_play.getLocalBounds().size;
	float pos_x = m_play_btn.getPosition().x + (PLAY_BTN_WIDTH - play_bounds.x) / 2;
	float pos_y = m_play_btn.getPosition().y + (PLAY_BTN_HEIGHT - play_bounds.y) / 2;
	m_txt_play.setPosition(sf::Vector2f(pos_x, pos_y));

	window.draw(m_play_btn);
	window.draw(m_txt_play);
}

void AGSnake2D::Main_Menu::set_is_visible(bool val)
{
	m_is_visible = val;
}

bool AGSnake2D::Main_Menu::get_is_visible()
{
	return m_is_visible;
}