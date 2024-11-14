#pragma once
#include"SFML/Graphics.hpp"
#include "Menu.h"
#include "World.h"

class Game{
private:
	sf::RenderWindow* window;
	sf::Event e;

	void init();
	void initWinow();
	void initVars();

	void update();
	void updateMenu();
	void updatePollEvents();

	Menu* menu;
	World* world;
	bool inMenu;

public:
	Game();
	~Game();

	void run();

	void render();

	sf::Event getEvent();
};
