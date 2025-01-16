#include "Player.h"
#include <iostream>

Player::Player(unsigned int joystickId) {
    this->joystickId = joystickId;
    this->speed = 100;
    tx.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling1.2.png");
    if (joystickId != 0) {
        tx.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling1.png");
    }
    sp.setTexture(tx);
    sp.setScale(0.8, 0.8);
    if (joystickId == 0) {
        sp.setPosition(50, 140);
    }
    else {
        sp.setScale(-.8, 0.8);
    }
    load_animations();
    frame_duration = 0.2f; // frame in s
    is_walking = false;
    is_animating = false;
    current_frame = 0;
}

void Player::update(sf::Time deltaTime) {
    move(deltaTime);

    if (is_walking) {
        start_animation(2);
    }
    else if (!is_walking) {
        is_animating = false;
        sp.setTexture(tx);
        current_frame = 0;
    }

    play_animation();
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
    else if (joystickId == 0) {
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
    if (movementX != 0) {
        is_walking = true;
    }
    else {
        is_walking = false;
    }

    sp.move(movementX, 0);
}

void Player::play_animation() {
    if (is_animating) {
        std::vector<sf::Texture>* currentAnimation = nullptr;

        switch (curr_a_i) {
        case 0:
            currentAnimation = &swordPullingTextures2;
            break;
        case 1:
            currentAnimation = &swordPullingTextures1;
            break;
        case 2:
            currentAnimation = (joystickId != 0) ? &walkingTextures1 : &walkingTextures2;
            break;
        }

        if (currentAnimation && clock.getElapsedTime().asSeconds() > frame_duration) {
            current_frame = (current_frame + 1) % currentAnimation->size();
            sp.setTexture((*currentAnimation)[current_frame]);
            clock.restart();

            if (curr_a_i != 2 && current_frame == currentAnimation->size() - 1) {
                is_animating = false;
            }
        }
    }
}

void Player::load_animations() {
    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture1;
        texture1.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling" + std::to_string(i) + ".png");
        swordPullingTextures1.push_back(texture1);

        sf::Texture texture2;
        texture2.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling" + std::to_string(i) + ".2.png");
        swordPullingTextures2.push_back(texture2);
    }
    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture1;
        texture1.loadFromFile("assets/Texture/walking1/animation-walking" + std::to_string(i) + ".png");
        walkingTextures1.push_back(texture1);

        sf::Texture texture2;
        texture2.loadFromFile("assets/Texture/walking2/animation-walking2." + std::to_string(i) + ".png");
        walkingTextures2.push_back(texture2);
    }

}

void Player::start_animation(int index) {
    if (is_animating && curr_a_i == index && index == 2) {
        return;
    }

    is_animating = true;
    curr_a_i = index;
    current_frame = 0;
    clock.restart();
}

void Player::setPosition(int a, int b) {
    sp.setPosition(a, b);
}

void Player::render(sf::RenderWindow* target) {
    target->draw(sp);
}

Player::~Player() {

}