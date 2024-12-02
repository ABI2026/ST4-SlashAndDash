#include "Player.h"

Player::Player() {
	this->speed = 100;
	tx.loadFromFile("assets/Texture/test player.png");
	sp.setTexture(tx);
	sp.setScale(0.5, 0.5);
}

Player::~Player() {

}

void Player::update(sf::Time deltaTime) {
	move(deltaTime);
}

void Player::render(sf::RenderWindow* target) {
	target->draw(sp);
}

void Player::move(sf::Time deltaTime) {
	float dt = deltaTime.asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->sp.move(this->speed * dt,0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->sp.move(this->speed * -dt, 0);
	}
}
