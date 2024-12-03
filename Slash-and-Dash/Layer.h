#pragma once
#include <string>
#include "SFML/Graphics.hpp"

class Layer {
	sf::Texture tx;
	float speed;

public:
	sf::Sprite sp;
	Layer(std::string path, float speed, int layerN);

	void update(float camOffset);
};
