#pragma once
#include"SFML/Graphics.hpp"
#include"string"

class World{
private:
<<<<<<< HEAD
	std::vector<sf::Texture> backgroundTextures;
	std::vector<sf::Texture> foregroundTextures;
	std::vector<sf::Texture> middlegroundTextures;
	
public:
	void push_back_backgroundTexture(string);
	void push_back_foregroundTexture(string);
	void push_back_middlegroundTexture(string);
	int getTheWorld(int, int, int);
=======
	float scaleX;
	float scaleY;
	float zentrierenX;
	float zentrierenY;


	std::vector<std::string> backgroundTextures;
	std::vector<std::string> foregroundTextures;
	std::vector<std::string> middlegroundTextures;
	
	sf::Texture fordergroundT;
	sf::Texture middlegroundT;
	sf::Texture backgroundT;

	sf::Sprite forground;
	sf::Sprite midground;
	sf::Sprite hintergrund;
public:
	World();
	World(sf::Vector2u windowSize);
	void push_back_backgroundTexture(std::string);
	void push_back_foregroundTexture(std::string);
	void push_back_middlegroundTexture(std::string);
	void loadTheWorld(int, int, int);
	
	void render(sf::RenderTarget* t);
>>>>>>> 9016be895c3a5eb6652ec39906545b9db22000ad
};


