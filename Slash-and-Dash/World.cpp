
#include "World.h"

World background;
World forderground;
World middleground;

void World::push_back_backgroundTexture(string b)
{
	background = b;
}

void World::push_back_foregroundTexture(string f)
{
	forderground = f;
}

void World::push_back_middlegroundTexture(string m)
{
	middleground = m;
}

void World::loadTheWorld(int a, int b, int c)
{
	sf::Texture fordergroundT;
	sf::Texture middlegroundT;
	sf::Texture backgroundT;
	
	if (!fordergroundT.loadFromFile(forderground[a])) {
		std::cout << "Fehler beim Laden des forderground!" << endl;
		return -1;
	}
	if (!middlegroundT.loadFromFile(middleground[b])) {
		std::cout << "Fehler beim Laden des middlegrounds!" << endl;
		retrun - 1;
	}
	if (!backgroundT.loadFromFile(background[c])) {
		std::cout << "Fehler beim Laden des backgrounds!" << endl;
	}
	
	sf::Sprite forground;
	sf::Sprite midground;
	sf::Sprite hintergrund;

	forground.setTexture(fordergroundT);
	midground.setTexture(middlegroundT);
	hintergrund.setTexture(backgroundT);
}
