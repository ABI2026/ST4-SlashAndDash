#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Debug_Menu
{
private:
;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape panel;

public:
	Debug_Menu();
	void update(Player* p, Player* p2, sf::RenderWindow* window);
	void render(sf::RenderWindow* target);
};

