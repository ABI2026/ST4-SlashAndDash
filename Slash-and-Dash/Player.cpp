#include "Player.h"

Player::Player(unsigned int joystickId){
    this->joystickId = joystickId;
	this->speed = 100;
	tx.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling4.png");
	sp.setTexture(tx);
	sp.setScale(0.8, 0.8);
	sp.setPosition(480, 140);
}

Player::~Player() {

}

void Player::update(sf::Time deltaTime) {
	move(deltaTime);
}

void Player::render(sf::RenderWindow* target) {
	target->draw(sp);
}

void Player::setPosition(int a, int b) {
    sp.setPosition(a, b);
}

void Player::move(sf::Time deltaTime) {
    float dt = deltaTime.asSeconds();
    float movementX = 0.0f;

    if (sf::Joystick::isConnected(joystickId)) {
        float axisX = sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X);
        if (axisX > 15) {
            movementX = this->speed * dt;
            sp.setScale(0.8, 0.8);
        }
        else if (axisX < -15) {
            movementX = this->speed * -dt;
            sp.setScale(-0.8, 0.8);
        }
    }
    else if(joystickId == 0){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (sp.getPosition().x + 20) < 960) {
            movementX = this->speed * dt;
            sp.setScale(0.8, 0.8);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sp.getPosition().x > 0) {
            movementX = this->speed * -dt;
            sp.setScale(-0.8, 0.8);
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && (sp.getPosition().x + 20) < 960) {
            movementX = this->speed * dt;
            sp.setScale(0.8, 0.8);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && sp.getPosition().x > 0) {
            movementX = this->speed * -dt;
            sp.setScale(-0.8, 0.8);
        }
    }

    sp.move(movementX, 0);
}
