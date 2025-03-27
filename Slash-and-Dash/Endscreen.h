#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

class Endscreen {
private:
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	float wait;
	float duration;
	bool render_screen;
	//Player* player;

	sf::Sprite spBackground, spPlayer;
	sf::Texture txBackground, txPlayer;


public:
	sf::Clock endscreenTime;
	bool winning_screen_started;

	Endscreen();
	void update(int num);
	void endscreen_start(float wait, float duration, int num);
	void start_winning_screen(float wait, float duration, int num);
	~Endscreen() {};
	void render(sf::RenderWindow* target);
	bool is_finished();
	bool getWinning_screen_started();
};
