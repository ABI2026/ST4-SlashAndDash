#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class Player
{
private:
	sf::Texture tx;
	sf::Sprite sp;
	std::vector<sf::Texture> playerTextures;
	int index;
	Game game;

	//player animation
	//std::vector<sf::IntRect> frames; // for Sprite Sheet Animation
	//int currentFrame;
	//float animationTimer;
	//float switchTime; 

public:
	Player(int index); //to chose different textures
	~Player();

	sf::FloatRect getBounds();
	std::vector<sf::Texture> addTexture(std::string file);
	void switchTexture(int index);

	void render(sf::RenderTarget* target);
	void movePlayer1();
	void movePlayer2();

};

