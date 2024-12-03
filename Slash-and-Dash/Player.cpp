#include "Player.h"

Player::Player() {
	this->speed = 100;
	tx.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling4.png");
	sp.setTexture(tx);
	sp.setScale(0.8, 0.8);
	sp.setPosition(480, + 140);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (sp.getPosition().x + 20) < 960) {
		this->sp.move(this->speed * dt,0);
		sp.setScale(0.8, 0.8);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sp.getPosition().x > 0) {
		this->sp.move(this->speed * -dt, 0);
		sp.setScale(-0.8, 0.8);
	}
}
