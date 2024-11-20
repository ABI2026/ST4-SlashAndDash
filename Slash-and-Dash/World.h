#pragma once
#include"SFML/Graphics.hpp"
#include"string"

class World{
private:
	std::vector<sf::Texture> backgroundTextures;
	std::vector<sf::Texture> foregroundTextures;
	std::vector<sf::Texture> middlegroundTextures;
	
public:
	void push_back_backgroundTexture(string);
	void push_back_foregroundTexture(string);
	void push_back_middlegroundTexture(string);
	int getTheWorld(int, int, int);
};


