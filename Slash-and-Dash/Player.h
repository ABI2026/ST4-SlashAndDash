#pragma once
#include "Animation_Player.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

class Player {
private:
    // Player properties
    unsigned int joystickId;
    float speed;
    bool is_walking;
    bool facing_right;

    // Rendering components
    sf::Sprite sp;
    sf::Texture tx;
    sf::RectangleShape hitbox;
    sf::RectangleShape attack_range;

    // Texture collections
    std::vector<sf::Texture> swordPullingTextures1, swordPullingTextures2;
    std::vector<sf::Texture> walkingTextures1, walkingTextures2;
    std::vector<sf::Texture> attackTextures1, attackTextures2;
    std::vector<sf::Texture> dyingTextures1, dyingTextures2;

    // Animation references
    std::vector<sf::Texture*> walkingRefs;
    std::vector<sf::Texture*> swordRefs;
    std::vector<sf::Texture*> attackRefs;
    std::vector<sf::Texture*> dyingRefs;

    // Animation controllers
    Animation_Player* walkingAnimation;
    Animation_Player* swordPullingAnimation;
    Animation_Player* attackAnimation;
    Animation_Player* dyingAnimation;

    // Initialization methods
    void initializeTextures();
    void initializeSprite();
    void initializeColliders();
    void load_animations();
    void loadTextureSet(std::vector<sf::Texture>& textureVec, const std::string& basePath,
        int startIdx, int endIdx, const std::string& suffix);
    void setupAnimations();
    void setupAnimationRefs(std::vector<sf::Texture*>& refs, std::vector<sf::Texture>& textures);

    // Update methods
    void updateColliders();
    void updateAnimations();
    float handleInput(float deltaTime);
    void setFacingDirection(bool faceRight);
    void move(sf::Time deltaTime);

public:
    Player(unsigned int joystickId);
    ~Player();

    // Public state
    bool is_attacking;
    bool is_alive;

    bool isDyingAnimationFinished() const {
        return !is_alive && dyingAnimation->isFinished();
    }

    // Gameplay methods
    void attack();
    void die();
    void update(sf::Time deltaTime);
    void start_animation(int index);
    void setPosition(int x, int y);
    void render(sf::RenderWindow* target);

    // Getters
    sf::Vector2f get_Position();
    sf::FloatRect get_attackBounds() { return attack_range.getGlobalBounds(); }
    sf::FloatRect get_globalBounds() { return hitbox.getGlobalBounds(); }
};