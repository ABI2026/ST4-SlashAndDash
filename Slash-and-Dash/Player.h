#pragma once
#include "SFML/Graphics.hpp"

class Player {
	sf::Texture tx;
	sf::Sprite sp;

	float speed;
public:
	Player();
	~Player();

	void update();
	void render(sf::RenderWindow* target);
	void move();
};
