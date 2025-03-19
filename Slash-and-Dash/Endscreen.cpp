#include "Endscreen.h"

Endscreen::Endscreen() {
	this->shape.setFillColor(sf::Color::Black);
	this->shape.setSize(sf::Vector2f(1000.f, 1000.f));
	this->shape.setPosition(0.f, 0.f);

	if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {}
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(60);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	text.setPosition(960 / 2, 540 / 2);
	render_screen = false;
}

void Endscreen::update(int num) {
	if (endscreenTime.getElapsedTime().asSeconds() >= duration && endscreenTime.getElapsedTime().asSeconds() < duration + 1) {
		render_screen = false;

	}

	if (endscreenTime.getElapsedTime().asSeconds() > wait && endscreenTime.getElapsedTime().asSeconds() <= duration) {
		render_screen = true;
	}
}

void Endscreen::endscreen_start(float wait, float duration, int num) {
	this->duration = duration;
	this->wait = wait;

	num == 0 ? text.setString("Player 1 won the round") : text.setString("Player 2 won the round");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	endscreenTime.restart();
}

void Endscreen::start_winning_screen(float wait, float duration, int num)
{
	this->duration = duration;
	this->wait = wait;

	num == 0 ? text.setString("Player 1 won the Game") : text.setString("Player 2 won the Game");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	endscreenTime.restart();
}

void Endscreen::render(sf::RenderWindow* target) {
	if (render_screen) {
		target->draw(shape);
		target->draw(text);
	}
}

bool Endscreen::is_finished()
{
	return endscreenTime.getElapsedTime().asSeconds() > duration;
}
