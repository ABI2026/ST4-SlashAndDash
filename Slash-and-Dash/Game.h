#pragma once
#include"SFML/Graphics.hpp"
#include "Menu.h"
#include "World.h"

class Game{
private:
	sf::RenderWindow* window;
	bool fullscreen;
	sf::Event e;

	int state; // 0 = Im Menue, 1 = Im Spiel

	sf::View gameView;
	float viewWidth;
	float viewHeight;

	Menu* menu;
	World* world;

	void init();
	void initWinow();
	void initVars();

	void update();
	void updateMenu();
	void updateView();
	void updatePollEvents();

public:
	Game();
	~Game();

	void run();

	void render();

	sf::Event getEvent();
};
