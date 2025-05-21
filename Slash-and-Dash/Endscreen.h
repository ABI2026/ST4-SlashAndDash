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
	sf::Sprite spCoin;
	sf::Texture txCoin;


public:
	sf::Clock endscreenTime;
	bool winning_screen_started;
	//bool winning_screen_or_end_screen; // true = endscrren false = winningscreen
	bool end_round_screen;
	bool winning_screen;
	float arrayCoinPlayer_x[6];
	float arrayCoinPlayer_y[6];

	bool coin1, coin2, coin3, coin4, coin5, coin6;
	sf::Sprite coinArr[6];

	Endscreen();
	void update(int countP1, int countP2, bool playerWon);
	void endscreen_start(float wait, float duration);
	void start_winning_screen(float wait, float duration, int num);
	~Endscreen() {};
	void render(sf::RenderWindow* target);
	void moveCoin(int coinIndex, int pointsP1, int pointsP2);
	bool is_finished();
	void reset_coin();
	void restart_time();
	bool is_winning_screen_started();
};
