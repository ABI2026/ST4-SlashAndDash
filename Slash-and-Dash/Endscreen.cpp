#include "Endscreen.h"

Endscreen::Endscreen() {

	if (!txBackground.loadFromFile("Assets/Texture/win-screen-hintergrund.png"));
	spBackground.setTexture(txBackground);
	spBackground.setScale(2.5f, 2.3f);

	//this->shape.setFillColor(sf::Color::Black);
	//this->shape.setSize(sf::Vector2f(1000.f, 1000.f));
	//this->shape.setPosition(0.f, 0.f);

	/*if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {}
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(60);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height);
	text.setPosition(480, 270);*/

	if (!txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png"));
	spPlayer.setTexture(txPlayer);
	spPlayer.setOrigin(spPlayer.getLocalBounds().width / 2, spPlayer.getLocalBounds().height);
	spPlayer.setPosition(480, 270);

	render_screen = false;
	winning_screen_started = false;
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

	num == 0 ? txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png")
		: txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png");
	spPlayer.setTexture(txPlayer);
	spPlayer.setOrigin(spPlayer.getLocalBounds().width / 2, spPlayer.getLocalBounds().height);
	endscreenTime.restart();
}

void Endscreen::start_winning_screen(float wait, float duration, int num)
{
	this->duration = duration;
	this->wait = wait;

	num == 0 ? txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png")
		: txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png");
	spPlayer.setTexture(txPlayer);
	spPlayer.setOrigin(spPlayer.getLocalBounds().width / 2, spPlayer.getLocalBounds().height);
	endscreenTime.restart();
	winning_screen_started = true;
}

void Endscreen::render(sf::RenderWindow* target) {
	if (render_screen) {
		target->draw(spBackground);
		target->draw(spPlayer);
	}
}

bool Endscreen::is_finished()
{
	return endscreenTime.getElapsedTime().asSeconds() > duration;
}

bool Endscreen::getWinning_screen_started()
{
	return winning_screen_started;
}

