#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

class Endscreen
{
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;

public:
	Endscreen();
	~Endscreen() {};
	void render(sf::RenderWindow* target);

};

