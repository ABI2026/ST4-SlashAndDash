#include "World.h"
#include <iostream>

World::World(){
	push_back_backgroundTexture("Assets/Texture/Sprite-0001background.png");  // Texturen ändern 
	push_back_foregroundTexture("Assets/Texture/trees.png");
	push_back_middlegroundTexture("Assets/Texture/mountains.png");
	push_back_durchsichtigVorne("Assets/Texture/Nebel-Hell.png");
	push_back_durchsichtigHinten("Assets/Texture/Nebel-Dunkel.png");
	loadTheWorld(0,0,0,0,0);
}
// wahrscheinlich unnötig
//World::World(sf::Vector2u windowSize)//Texturengr��e richtig skalieren 
//{
//
//	sf::Vector2u texturGrossefront = fordergroundT.getSize();
//	sf::Vector2u texturGrossemid = middlegroundT.getSize();
//	sf::Vector2u texturGrosseback = backgroundT.getSize();
//
//	 //scaleX = static_cast<float>(windowSize.x) / texturGrosseback.x;
//	 //scaleY = static_cast<float>(windowSize.y) / texturGrosseback.y;
//
//	 zentrierenX = windowSize.x;
//	 zentrierenY = windowSize.y;
//
//}
// Grafiken hinzufügen
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

void World::push_back_durchsichtigVorne(std::string durch_Vorne)
{
	durchsicht_nah_Texture.push_back(durch_Vorne);
}

void World::push_back_durchsichtigHinten(std::string durch_Hinten)
{
	durchsicht_weit_Texture.push_back(durch_Hinten);
}
// ende Methoden Grafiken hinzufügen
// Grafiken zeigen laden
void World::loadTheWorld(int a, int b, int c, int d, int e)
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
	if (!durchsichtig_nah.loadFromFile(durchsicht_nah_Texture[d])) {
		//std::cout << "Fehler beim Laden des backgrounds!" << endl;
		//return 0;
	}
	if (!durchsichtig_weit.loadFromFile(durchsicht_weit_Texture[e])) {
		//std::cout << "Fehler beim Laden des backgrounds!" << endl;
		//return 0;
	}

	durchsichtW.setTexture(durchsichtig_weit);
	durchsichtH.setTexture(durchsichtig_nah);
	forground.setTexture(fordergroundT);
	midground.setTexture(middlegroundT);
	hintergrund.setTexture(backgroundT);
}
//Parallax Effekt Funktion 
void World::paraMove()
{

}

//Parallax Effekt funktion
//void World::moveParaEffekt()
//{
//	sf::Clock clock;
//	float elapsedTime = clock.getElapsedTime().asSeconds();
//	while () {
//		if ()
//
//
//
//
//	}
//}

// update Grafiken abh�ngig von dem Fenster

void World::render(sf::RenderTarget* t){
	

	//sf::Vector2u fensterGroesse = window.getSize();  //fenstergr��e bestimmen
	//sf::Vector2u texturGroesse = textur.getSize();  //texturgr��e bestimmen
	
	t->draw(hintergrund);
	//t->draw(durchsichtW); //zwie layers sind zu viel
	t->draw(midground);
	//t->draw(durchsichtH);
	t->draw(forground);
	

	hintergrund.setPosition(-10,0);
	hintergrund.setScale(0.79,0.6);
	midground.setPosition(0, 50);
	midground.setScale(0, 0);
	forground.setPosition(0, 0);
	forground.setScale(0, 0);
	//hintergrund.setOrigin(texturGrosseback.x / 2.0f, textureSize.y / 2.0f);
}
