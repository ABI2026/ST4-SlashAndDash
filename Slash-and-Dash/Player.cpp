#include "Player.h"

Player::Player() {
	this->speed = 1.5;
	tx.loadFromFile("assets/Texture/test player.png");
	sp.setTexture(tx);
	sp.setScale(0.5, 0.5);
}

Player::~Player() {

}

void Player::update() {
	move();
}

void Player::render(sf::RenderWindow* target) {
	target->draw(sp);
}

void Player::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->sp.move(this->speed * 1,0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->sp.move(this->speed * -1, 0);
	}
}
