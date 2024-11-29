#pragma once
#include"SFML/Graphics.hpp"
#include"string"

class World{
private:
	float scaleX;
	float scaleY;
	float zentrierenX;
	float zentrierenY;
	

	std::vector<std::string> backgroundTextures;
	std::vector<std::string> foregroundTextures;
	std::vector<std::string> middlegroundTextures;
	std::vector<std::string> durchsicht_nah_Texture;
	std::vector<std::string> durchsicht_weit_Texture;

	sf::Texture durchsichtig_weit;
	sf::Texture durchsichtig_nah;
	sf::Texture fordergroundT;
	sf::Texture middlegroundT;
	sf::Texture backgroundT;

	sf::Sprite durchsichtW;
	sf::Sprite durchsichtH;
	sf::Sprite forground;
	sf::Sprite midground;
	sf::Sprite hintergrund;
public:
	World();
	/*World(sf::Vector2u windowSize);*/
	void push_back_backgroundTexture(std::string);
	void push_back_foregroundTexture(std::string);
	void push_back_middlegroundTexture(std::string);
	void push_back_durchsichtigVorne(std::string);
	void push_back_durchsichtigHinten(std::string);
	void loadTheWorld(int, int, int, int, int);
	void paraMove();
	//void moveParaEffekt();

	
	void render(sf::RenderTarget* t);
};


