#pragma once
#include"SFML/Graphics.hpp"
#include "Menu.h"
#include "World.h"
#include "SFML/Audio.hpp"

class Player;

class Game{
private:
	sf::RenderWindow* window;
	bool fullscreen;
	sf::Event e;

	sf::Music mBg;

	enum State {
		inMainMenu,
		inGameMenu,
		Playing
	};
	State state;

	sf::View gameView;
	float viewWidth;
	float viewHeight;


	Menu* menu;
	World* world;
	Player* player;
	Player* player2;

	void init();
	void initWinow();
	void initVars();
	void initPlayer();

	void update(sf::Time deltaTime);
	void updateMenu();
	void updateView();
	void updatePlayer(sf::Time deltaTime);
	void updatePollEvents();

public:
	Game();
	virtual ~Game();

	void run();

	void render();

	sf::Event getEvent();
};
