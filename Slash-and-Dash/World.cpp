#include "World.h"
#include <iostream>

<<<<<<< HEAD
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
=======
World::World(){
	push_back_backgroundTexture("Assets/Texture/far-mountains.png");
	push_back_foregroundTexture("Assets/Texture/trees.png");
	push_back_middlegroundTexture("Assets/Texture/mountains.png");
	loadTheWorld(0,0,0);
}

World::World(sf::Vector2u windowSize)//Texturengr��e richtig skalieren 
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
>>>>>>> 9016be895c3a5eb6652ec39906545b9db22000ad
}

void World::loadTheWorld(int a, int b, int c)
{
<<<<<<< HEAD
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
=======

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

>>>>>>> 9016be895c3a5eb6652ec39906545b9db22000ad

	forground.setTexture(fordergroundT);
	midground.setTexture(middlegroundT);
	hintergrund.setTexture(backgroundT);
<<<<<<< HEAD
=======
}
// update Grafiken abh�ngig von dem Fenster

void World::render(sf::RenderTarget* t){
	

	//sf::Vector2u fensterGroesse = window.getSize();  //fenstergr��e bestimmen
	//sf::Vector2u texturGroesse = textur.getSize();  //texturgr��e bestimmen


	t->draw(hintergrund);
	t->draw(midground);
	t->draw(forground);
	
	hintergrund.setPosition(zentrierenX / 2.0f, zentrierenY / 2.0f);
	hintergrund.setScale(scaleX, scaleY);
	midground.setPosition(0, 200);
	midground.setScale(2, 2);
	forground.setPosition(0, 0);
	forground.setScale(1, 2);
	//hintergrund.setOrigin(texturGrosseback.x / 2.0f, textureSize.y / 2.0f);
>>>>>>> 9016be895c3a5eb6652ec39906545b9db22000ad
}
