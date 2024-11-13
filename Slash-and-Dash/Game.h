#pragma once
#include"SFML/Graphics.hpp"
#include "Menu.h"

class Game{
private:
	sf::RenderWindow* window;

	void init();
	void initWinow();
	void initVars();

	void update();
	void updateMenu();
	void updatePollEvents();

	Menu* menu;
	bool inMenu;

public:
	Game();
	~Game();

	void run();

	void render();
};
