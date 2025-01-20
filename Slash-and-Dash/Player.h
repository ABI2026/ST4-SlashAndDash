#pragma once
#include "Animation_Player.h"
#include "SFML/Graphics.hpp"

class Player {
private:
    unsigned int joystickId;
    float speed;
    sf::Sprite sp;
    sf::Texture tx;

    // Texturen als Vektoren
    std::vector<sf::Texture> swordPullingTextures1;
    std::vector<sf::Texture> swordPullingTextures2;
    std::vector<sf::Texture> walkingTextures1;
    std::vector<sf::Texture> walkingTextures2;

    // Referenzen auf die Texturen
    std::vector<sf::Texture*> walkingRefs;
    std::vector<sf::Texture*> swordRefs;
    Animation_Player* walkingAnimation;
    Animation_Player* swordPullingAnimation;
    bool is_walking;

    float getMovementInput();
    void load_animations();
    void move(sf::Time deltaTime);
    void setupAnimations();

public:
    Player(unsigned int joystickId);
    ~Player();
    void update(sf::Time deltaTime);
    sf::Vector2f get_Position();
    void start_animation(int index);
    void setPosition(int x, int y);
    void render(sf::RenderWindow* target);
};
