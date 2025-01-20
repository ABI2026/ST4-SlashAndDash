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
    setupAnimations();
    is_walking = false;
}

void Player::setupAnimations() {
    if (joystickId != 0) {
        for (sf::Texture& tex : walkingTextures1) {
            walkingRefs.push_back(&tex);
        }
    }
    else {
        for (sf::Texture& tex : walkingTextures2) {
            walkingRefs.push_back(&tex);
        }
    }
    walkingAnimation = new Animation_Player(&sp, walkingRefs, 0.2f);

    if (joystickId != 0) {
        for (sf::Texture& tex : swordPullingTextures1) {
            swordRefs.push_back(&tex);
        }
    }
    else {
        for (sf::Texture& tex : swordPullingTextures2) {
            swordRefs.push_back(&tex);
        }
    }
    swordPullingAnimation = new Animation_Player(&sp, swordRefs, 0.2f);
}

void Player::load_animations() {
    // Texturen laden
    for (int i = 1; i <= 4; ++i) {
        sf::Texture tex1, tex2;
        tex1.loadFromFile("assets/Texture/swordpulling/animation-sword-pulling" + std::to_string(i) + ".png");
        tex2.loadFromFile("assets/Texture/swordpulling2/animation-sword-pulling" + std::to_string(i) + ".2.png");
        swordPullingTextures1.push_back(tex1);
        swordPullingTextures2.push_back(tex2);
    }

    for (int i = 1; i <= 7; ++i) {
        sf::Texture tex1, tex2;
        tex1.loadFromFile("assets/Texture/walking1/animation-walking" + std::to_string(i) + ".png");
        tex2.loadFromFile("assets/Texture/walking2/animation-walking2." + std::to_string(i) + ".png");
        walkingTextures1.push_back(tex1);
        walkingTextures2.push_back(tex2);
    }
}

void Player::update(sf::Time deltaTime) {
    move(deltaTime);

    if (is_walking) {
        if (!walkingAnimation->isPlaying()) {
            walkingAnimation->play(true);
        }
    }
    else {
        walkingAnimation->stop();
        sp.setTexture(tx);
    }

    walkingAnimation->update();
    swordPullingAnimation->update();
}

sf::Vector2f Player::get_Position() {
    return sp.getPosition();
}

void Player::start_animation(int index) {
    switch (index) {
    case 0:
        swordPullingAnimation->play(false);
        break;
    case 1:
        break;
    case 2:
        walkingAnimation->play(true);
        break;

    default:
        break;
    }
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

    is_walking = (movementX != 0);
    sp.move(movementX, 0);
}

void Player::setPosition(int x, int y) {
    sp.setPosition(x, y);
}

void Player::render(sf::RenderWindow* target) {
    target->draw(sp);
}

Player::~Player() {
    delete walkingAnimation;
    delete swordPullingAnimation;
}