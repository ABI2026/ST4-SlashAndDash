#pragma once
#include "Animation_Player.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Player {
private:
    unsigned int joystickId;
    float speed;

    sf::Sprite sp;
    sf::Texture tx;

    sf::RectangleShape hitbox;
    sf::RectangleShape attack_range;

    // Texturen als Vektoren
    std::vector<sf::Texture> swordPullingTextures1, swordPullingTextures2;
    std::vector<sf::Texture> walkingTextures1, walkingTextures2;
    std::vector<sf::Texture> attackTextures1, attackTextures2;

    // Referenzen auf die Texturen
    std::vector<sf::Texture*> walkingRefs;
    std::vector<sf::Texture*> swordRefs;
    std::vector<sf::Texture*> attackRefs;
    Animation_Player* walkingAnimation;
    Animation_Player* swordPullingAnimation;
    Animation_Player* attackAnimation;
    bool is_walking;
    bool is_alive;

    void load_animations();
    void move(sf::Time deltaTime);
    void setupAnimations();

public:
    Player(unsigned int joystickId);
    ~Player();

    bool is_attacking;
    bool facing_right;

    void attack();

    sf::FloatRect get_attackBounds() {
        return attack_range.getGlobalBounds();
    }
    sf::FloatRect get_globalBounds() {
        return hitbox.getGlobalBounds();
    }

    void update(sf::Time deltaTime);
    sf::Vector2f get_Position();
    void start_animation(int index);
    void die();
    void setPosition(int x, int y);
    void render(sf::RenderWindow* target);
};