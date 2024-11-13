#include "World.h"
#include <iostream>

World::World(){
	push_back_backgroundTexture("Assets/Texture/far-mountains.png");
	push_back_foregroundTexture("Assets/Texture/trees.png");
	push_back_middlegroundTexture("Assets/Texture/mountains.png");
	loadTheWorld(0,0,0);
}

World::World(sf::Vector2u windowSize)//Texturengröße richtig skalieren 
{
	sf::Vector2u texturGrossefront = fordergroundT.getSize();
	sf::Vector2u texturGrossemid = middlegroundT.getSize();
	sf::Vector2u texturGrosseback = backgroundT.getSize();
}

void World::push_back_backgroundTexture(std::string b)
{
	backgroundTextures.push_back(b);
}

void World::push_back_foregroundTexture(std::string f)
{
	foregroundTextures.push_back(f);
}

void World::push_back_middlegroundTexture(std::string m)
{
	middlegroundTextures.push_back(m);
}

void World::loadTheWorld(int a, int b, int c)
{

	if (!fordergroundT.loadFromFile(foregroundTextures[a])) {
		//std::cout << "Fehler beim Laden des forderground!" << endl;
		//return 0;
	}
	if (!middlegroundT.loadFromFile(middlegroundTextures[b])) {
		//std::cout << "Fehler beim Laden des middlegrounds!" << endl;
		//retrun 0;
	}
	if (!backgroundT.loadFromFile(backgroundTextures[c])) {
		//std::cout << "Fehler beim Laden des backgrounds!" << endl;
		//return 0;
	}


	forground.setTexture(fordergroundT);
	midground.setTexture(middlegroundT);
	hintergrund.setTexture(backgroundT);
}

void World::render(sf::RenderTarget* t){
	

	//sf::Vector2u fensterGroesse = window.getSize();  //fenstergröße bestimmen
	//sf::Vector2u texturGroesse = textur.getSize();  //texturgröße bestimmen


	t->draw(hintergrund);
	t->draw(midground);
	t->draw(forground);
	
	forground.setPosition(0, 400);
	forground.setScale(1, 1);
	midground.setPosition(0, 200);
	midground.setScale(2, 2);
	hintergrund.setPosition(0, -400);
	hintergrund.setScale(5, 5);
	
}
