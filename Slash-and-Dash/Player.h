#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Texture tx;
	sf::Sprite sp;
	sf::Texture playerTextures;
	int index;
	sf::Event ev;

	//player animation
	//std::vector<sf::IntRect> frames; // for Sprite Sheet Animation
	//int currentFrame;
	//float animationTimer;
	//float switchTime; 

public:
	Player(); //to chose different textures
	~Player();

	sf::FloatRect getBounds();
	void addTexture(std::string file);
	void switchTexture(int index);

	void render(sf::RenderTarget* target);
	void movePlayer1();
	void movePlayer2();

};

