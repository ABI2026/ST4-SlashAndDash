#pragma once
#include "SFML/Graphics.hpp"

class Player {
	static int a;

	sf::Texture tx;
	sf::Sprite sp;
	sf::Clock clock;

	sf::Texture texture1, texture2, texture3, texture4;

	int current_frame = 0;
	int curr_a_i;
	float frame_duration = 0.25;
	bool is_animating = false;

	std::vector<sf::Texture> swordPullingTextures1;
	std::vector<sf::Texture> swordPullingTextures2;

	void play_animation();

	unsigned int joystickId;

	float speed;
public:
	Player(unsigned int joystickId);
	~Player();

	void update(sf::Time deltaTime);
	void move(sf::Time deltaTime);
	void start_animation(int);
	void load_animations();
	void render(sf::RenderWindow* target);

	void setPosition(int a, int b);

	sf::Vector2f getPosition() const {
		return sp.getPosition();
	}
};
