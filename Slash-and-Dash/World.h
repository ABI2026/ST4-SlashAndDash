#pragma once
#include<vector>
#include <cstdlib>
#include <ctime>
#include "Layer.h"
#include"SFML/Graphics.hpp"

class World{
	std::vector<std::vector<Layer*>> level;
	int lvlIndex;
	sf::Sprite sp;
	sf::Texture tx;
	void loadLvl();
	void setRandomLevel();

public:
	World();
	~World();

	void setLvl(int index);
	void update(float camOff);
	void render(sf::RenderTarget* target);
};
