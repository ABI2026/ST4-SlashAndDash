#include "Debug_Menu.h"
using namespace std;

Debug_Menu::Debug_Menu()
{
	panel.setSize(sf::Vector2f(240.f, 70.f));
	panel.setFillColor(sf::Color(0, 0, 0, 150));
	panel.setPosition(10.f, 10.f);

	if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {}
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(20);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	text.setPosition(130.f, 70.f);
}

void Debug_Menu::update(Player* p, Player* p2, sf::RenderWindow* window)
{
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*window);
	sf::Vector2f mouseWorldPos = window->mapPixelToCoords(mousePixelPos);

	text.setString(
		"Player 1: X : " + std::to_string(p->get_PositionX()) + "\n" +
		"Player 2: X : " + std::to_string(p2->get_PositionX()) + "\n" +
		"Mouse: X : " + std::to_string((int)mouseWorldPos.x) +
		" Y : " + std::to_string((int)mouseWorldPos.y)
	);

	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
}

void Debug_Menu::render(sf::RenderWindow* target)
{
	target->draw(panel);
	target->draw(text);
}
