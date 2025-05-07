#include "Endscreen.h"

Endscreen::Endscreen() {

	if (!txBackground.loadFromFile("Assets/Texture/win-screen-hintergrund.png"));
	spBackground.setTexture(txBackground);
	spBackground.setScale(2.5f, 2.3f);

	if (!txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png"));
	spPlayer.setTexture(txPlayer);
	spPlayer.setOrigin(spPlayer.getLocalBounds().width / 2, spPlayer.getLocalBounds().height / 2);
	spPlayer.setPosition(480, 510);

	if (!txCoin.loadFromFile("Assets/Texture/lifebar-coin-ver2-final.png")) return;
	spCoin.setTexture(txCoin);
	spCoin.setOrigin(spCoin.getLocalBounds().width / 2, spCoin.getLocalBounds().height / 2);
	spCoin.setPosition(480, 275);

	render_screen = false;
	winning_screen = false;
	end_round_screen = false;
}

void Endscreen::update() {
	/*if (endscreenTime.getElapsedTime().asSeconds() >= duration && endscreenTime.getElapsedTime().asSeconds() < duration + 1) {
		render_screen = false;

	}

	if (endscreenTime.getElapsedTime().asSeconds() > wait && endscreenTime.getElapsedTime().asSeconds() <= duration) {
		render_screen = true;
	}*/

	float elapsed = endscreenTime.getElapsedTime().asSeconds();

	if (elapsed >= wait && elapsed < wait + duration) {
		render_screen = true;
	}
	else {
		render_screen = false;
	}

	if(end_round_screen && elapsed >= 1.4) moveCoin(0);

	if (is_finished()) { 
		end_round_screen = false;
		reset_coin();
	}
}


void Endscreen::endscreen_start(float wait, float duration) {

	endscreenTime.restart();
	end_round_screen = true;

	this->duration = duration;
	this->wait = wait;

	spCoin.setScale(12.f, 12.f);
	
	//cout << spCoin.getPosition().x << " " << spCoin.getPosition().y << endl;
	endscreenTime.restart();
}

void Endscreen::start_winning_screen(float wait, float duration, int num)
{
	this->duration = duration;
	this->wait = wait;
	winning_screen = true;

	num == 0 ? txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png")
		: txPlayer.loadFromFile("Assets/Texture/win-screen-player1.png");
	spPlayer.setTexture(txPlayer);
	spPlayer.setOrigin(spPlayer.getLocalBounds().width / 2, spPlayer.getLocalBounds().height);
	spPlayer.setScale(2.f, 2.f);
	endscreenTime.restart();
}

void Endscreen::render(sf::RenderWindow* target) {
	
	if (render_screen) {
		if (winning_screen) {
			target->draw(spBackground);
			target->draw(spPlayer);
		}
		else if (end_round_screen && endscreenTime.getElapsedTime().asSeconds() < wait + duration) {
			target->draw(spCoin);
		}

		// Wenn der Endscreen vorbei ist, schalte alles aus
		if (endscreenTime.getElapsedTime().asSeconds() >= wait + duration) {
			render_screen = false;
			winning_screen = false;
			end_round_screen = false;
		}
	}
}

void Endscreen::moveCoin(int coinIndex)
{

	sf::Vector2f targetPos;
	float moveX = 0.f, moveY = 0.f;
	float shrinkFactor = 0.f;

	switch (coinIndex) {
	case 0:
		targetPos = sf::Vector2f(60.f, 60.f);
		moveX = -3.f;
		moveY = -1.6f;
		shrinkFactor = 0.988f;
		break;
	case 1: //nicht fertig
		targetPos = sf::Vector2f(120.f, 80.f);
		moveX = -2.5f;
		moveY = -1.2f;
		shrinkFactor = 0.99f;
		break;
	case 2: // nicht fertig
		targetPos = sf::Vector2f(180.f, 100.f);
		moveX = -2.f;
		moveY = -1.0f;
		shrinkFactor = 0.985f;
		break;
	default:
		return; 
	}

	// Aktuelle Position
	sf::Vector2f pos = spCoin.getPosition();

	if (pos.y > targetPos.y || pos.x > targetPos.x) {

		spCoin.move(moveX, moveY);

		sf::Vector2f scale = spCoin.getScale();

		if (scale.x > 0.1f && scale.y > 0.1f) {
			spCoin.setScale(scale.x * shrinkFactor, scale.y * shrinkFactor);
		}
	}

	arrayCoinPlayer_x[coinIndex] = spCoin.getPosition().x;
	arrayCoinPlayer_y[coinIndex] = spCoin.getPosition().y;
}

bool Endscreen::is_finished()
{
	return endscreenTime.getElapsedTime().asSeconds() > duration;
}

void Endscreen::reset_coin()
{
	spCoin.setPosition(480, 275);
}

void Endscreen::restart_time()
{
	endscreenTime.restart();
}

bool Endscreen::is_winning_screen_started()
{
	return winning_screen;
}

