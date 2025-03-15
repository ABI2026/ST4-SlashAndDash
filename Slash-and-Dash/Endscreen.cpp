#include "Endscreen.h"

Endscreen::Endscreen() {
	this->shape.setFillColor(sf::Color::Black);
	this->shape.setSize(sf::Vector2f(1000.f, 1000.f));
	this->shape.setPosition(0.f, 0.f);

	if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {}
	text.setFont(font);
	//player->getJoystickID() == 0 ? text.setString("Player 1 won the round") : text.setString("Player 2 won the round");
	//text.setString("");
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
	num == 0 ? text.setString("Player 1 won the round") : text.setString("Player 2 won the round");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	text.setPosition(960 / 2, 540 / 2);
}

void Endscreen::endscreen_start(float wait, float duration) {
	this->duration = duration;
	this->wait = wait;
	endscreenTime.restart();
}

void Endscreen::render(sf::RenderWindow* target) {
	if (render_screen) {
		target->draw(shape);
		target->draw(text);
	}
	//cout << "Endscreen wurde gezeichnet" << endl;
}

bool Endscreen::is_finished()
{
	return endscreenTime.getElapsedTime().asSeconds() > duration;
}
