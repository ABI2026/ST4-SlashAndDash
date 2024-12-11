#pragma once
#include "SFML/Graphics.hpp"

class Player {
	sf::Texture tx;
	sf::Sprite sp;

	unsigned int joystickId;

	float speed;
public:
	Player(unsigned int joystickId);
	~Player();

	void update(sf::Time deltaTime);
	void move(sf::Time deltaTime);
	void render(sf::RenderWindow* target);

	void setPosition(int a, int b);

	sf::Vector2f getPosition() const {
		return sp.getPosition();
	}
};
