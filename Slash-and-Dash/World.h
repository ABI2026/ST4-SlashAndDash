#pragma once
#include"SFML/Graphics.hpp"
#include"string"

class World{
private:
	std::vector<sf::Texture> backgroundTextures;
	std::vector<sf::Texture> foregroundTextures;
	std::vector<sf::Texture> middlegroundTextures;
public:
	void push_back_backgroundTexture();
	void push_back_foregroundTexture();
	void push_back_middlegroundTexture();
	
};


