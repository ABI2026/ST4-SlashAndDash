#pragma once
#include "SFML/Graphics.hpp"

class Player {
	sf::Texture tx;
	sf::Sprite sp;

	float speed;
public:
	Player();
	~Player();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* target);
	void move(sf::Time deltaTime);
};
