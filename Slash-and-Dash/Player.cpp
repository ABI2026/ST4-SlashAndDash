#include "Player.h"
#include <iostream>

int Player::a = 1;

Player::Player(unsigned int joystickId){
    this->joystickId = joystickId;
	this->speed = 100;
    tx.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling1.2.png");
    if(a != 1){
        tx.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling1.png");
    }
	sp.setTexture(tx);
	sp.setScale(0.8, 0.8);
    if (a == 1) {
        sp.setPosition(50, 140);
    }
    else {
        sp.setScale(-.8, 0.8);
    }
    a++;
    load_animations();
}

Player::~Player() {

}

void Player::update(sf::Time deltaTime) {
	move(deltaTime);
    play_animation();
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

void Player::play_animation() {
    if (curr_a_i == 1 && is_animating) {
        if (clock.getElapsedTime().asSeconds() > frame_duration && current_frame < swordPullingTextures1.size()- 1) {
            current_frame += 1;
            sp.setTexture(swordPullingTextures1[current_frame]);
            clock.restart();
        }
        else if (current_frame == swordPullingTextures1.size()) {
            is_animating = false;
        }
    }
    if (curr_a_i == 0 && is_animating) {
        if (clock.getElapsedTime().asSeconds() > frame_duration && current_frame < swordPullingTextures2.size() - 1) {
            current_frame += 1;
            sp.setTexture(swordPullingTextures2[current_frame]);
            clock.restart();
        }
        else if (current_frame == swordPullingTextures2.size()) {
            is_animating = false;
        }
    }
}

void Player::load_animations() {
    texture1.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling1.png");
    texture2.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling2.png");
    texture3.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling3.png");
    texture4.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling4.png");
    swordPullingTextures1.push_back(texture1);
    swordPullingTextures1.push_back(texture2);
    swordPullingTextures1.push_back(texture3);
    swordPullingTextures1.push_back(texture4);

    texture1.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling1.2.png");
    texture2.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling2.2.png");
    texture3.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling3.2.png");
    texture4.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling4.2.png");
    swordPullingTextures2.push_back(texture1);
    swordPullingTextures2.push_back(texture2);
    swordPullingTextures2.push_back(texture3);
    swordPullingTextures2.push_back(texture4);
}

void Player::start_animation(int index) {
    is_animating = true;
    curr_a_i = index;
    current_frame = 0;
    clock.restart();
}