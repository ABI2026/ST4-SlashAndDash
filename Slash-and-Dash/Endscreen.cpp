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
	render_screen = false;
}

void Endscreen::update()
{
	if (endscreenTime.getElapsedTime().asSeconds() >= duration && endscreenTime.getElapsedTime().asSeconds() < duration + 1) {
		render_screen = false;
		
	}

	if (endscreenTime.getElapsedTime().asSeconds() > wait && endscreenTime.getElapsedTime().asSeconds() <= duration) {
		render_screen = true;
	}
}

void Endscreen::endscreen_start(float wait, float duration)
{
	this->duration = duration;
	this->wait = wait;
	endscreenTime.restart();
}

void Endscreen::render(sf::RenderWindow* target)
{
	if (render_screen) {
		target->draw(shape);
		target->draw(text);
	}
	//cout << "Endscreen wurde gezeichnet" << endl;
}
