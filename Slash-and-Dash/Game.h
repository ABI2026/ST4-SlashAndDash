#pragma once
#include"SFML/Graphics.hpp"

class Game{
private:
	sf::RenderWindow* window;

public:
	Game();
	~Game();

	void run();

	void init();
	void initWinow();

	void update();
	void updatePollEvents();

	void render();
};

