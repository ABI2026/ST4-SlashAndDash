#include "Endscreen.h"

Endscreen::Endscreen()
{
	this->shape.setFillColor(sf::Color::Black);
	this->shape.setSize(sf::Vector2f(1000.f, 1000.f));
	this->shape.setPosition(0.f, 0.f);

	if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {}
	text.setFont(font);
	text.setString("Game over");
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(120);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	text.setPosition(960 / 2, 540 / 2);
	
}

void Endscreen::render(sf::RenderWindow* target)
{

	target->draw(shape);
	target->draw(text);
	//cout << "Endscreen wurde gezeichnet" << endl;
}
