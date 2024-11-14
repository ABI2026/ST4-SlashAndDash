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

	 scaleX = static_cast<float>(windowSize.x) / texturGrosseback.x;
	 scaleY = static_cast<float>(windowSize.y) / texturGrosseback.y;

	 zentrierenX = windowSize.x;
	 zentrierenY = windowSize.y;

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
// update Grafiken abhängig von dem Fenster

void World::render(sf::RenderTarget* t){
	

	//sf::Vector2u fensterGroesse = window.getSize();  //fenstergröße bestimmen
	//sf::Vector2u texturGroesse = textur.getSize();  //texturgröße bestimmen


	t->draw(hintergrund);
	t->draw(midground);
	t->draw(forground);
	
	hintergrund.setPosition(zentrierenX / 2.0f, zentrierenY / 2.0f);
	hintergrund.setScale(scaleX, scaleY);
	midground.setPosition(0, 200);
	midground.setScale(2, 2);
	forground.setPosition(0, 0);
	forground.setScale(1, 2);
	hintergrund.setOrigin(texturGrosseback.x / 2.0f, textureSize.y / 2.0f);
}
