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
	coin1 = false, coin2 = false, coin3 = false, coin4 = false, coin5 = false, coin6 = false;

	for (int i = 0; i < 6; i++) {
		coinArr[i].setTexture(txCoin);
	}

	coinArr[0].setOrigin(coinArr[0].getLocalBounds().width / 2, coinArr[0].getLocalBounds().height / 2);
	coinArr[0].setPosition(60.f, 50.f);
	coinArr[0].setScale(2.21387f, 2.21387f);

	coinArr[1].setOrigin(coinArr[0].getLocalBounds().width / 2, coinArr[0].getLocalBounds().height / 2);
	coinArr[1].setPosition(170.f, 50.f);
	coinArr[1].setScale(2.21387f, 2.21387f);
}

void Endscreen::update(int countP1, int countP2) {
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

	if(end_round_screen && elapsed >= 1.4 && countP1 == 1) moveCoin(0, countP1, countP2);
	if (end_round_screen && elapsed >= 1.4 && countP1 == 2) moveCoin(1, countP1, countP2);
	if (end_round_screen && elapsed >= 1.4 && countP1 == 3) moveCoin(2, countP1, countP2);
	if (end_round_screen && elapsed >= 1.4 && countP2 == 4) moveCoin(3, countP1, countP2);
	if (end_round_screen && elapsed >= 1.4 && countP2 == 5) moveCoin(4, countP1, countP2);
	if (end_round_screen && elapsed >= 1.4 && countP2 == 6) moveCoin(5, countP1, countP2);
	

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
		cout << spCoin.getScale().x << " " << spCoin.getScale().y << endl;
	
		// Wenn der Endscreen vorbei ist, schalte alles aus
		if (endscreenTime.getElapsedTime().asSeconds() >= wait + duration) {
			render_screen = false;
			winning_screen = false;
			end_round_screen = false;
		}
	}

	if (coin1 && !winning_screen) target->draw(coinArr[0]);
	if (coin2 && !winning_screen) target->draw(coinArr[1]);
	if (coin3) target->draw(coinArr[2]);
	if (coin4) target->draw(coinArr[3]);
	if (coin5) target->draw(coinArr[4]);
	if (coin6) target->draw(coinArr[5]);
}

void Endscreen::moveCoin(int coinIndex, int pointsP1, int pointsP2)
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
		//coin1 = true;
		break;
	case 1: //nicht fertig
		targetPos = sf::Vector2f(170.f, 60.f);
		moveX = -2.8f;
		moveY = -2.f;
		shrinkFactor = 0.980f;
		//coin2 = true;
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

		if (scale.x > 2.21387f && scale.y > 2.21387f) {
			spCoin.setScale(scale.x * shrinkFactor, scale.y * shrinkFactor);
		}
	}
	else { 
		if(pointsP1 >= 1) coin1 = true;
		if (pointsP1 >= 2) coin2 = true;
		if (pointsP1 >= 3) coin3 = true;
		if (pointsP2 >= 1) coin4 = true;
		if (pointsP2 >= 2) coin5 = true;
		if (pointsP2 >= 3) coin6 = true;

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

