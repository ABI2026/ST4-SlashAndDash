#pragma once
#include"SFML/Graphics.hpp"

class Game{
private:
	sf::RenderWindow* window;

	void init();
	void initWinow();

public:
	Game();
	~Game();

	void run();

	void update();
	void updatePollEvents();

	void render();
};

