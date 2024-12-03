#include "Layer.h"

Layer::Layer(std::string path, float speed, int layerN) {
	tx.loadFromFile(path);
	sp.setTexture(tx);
	switch (layerN) {
	case 1:
		sp.setScale(3.067, 3.067);
		sp.setOrigin(0, 50);
		sp.setPosition(-40, 0);
		break;
	case 2:
		sp.setScale(3.067, 3.067);
		sp.setOrigin(0, 40);
		sp.setPosition(-25, 0);
		break;
	case 3:
		sp.setScale(3.067, 3.067);
		break;
	}
	this->speed = speed;
}

void Layer::update(float playerMovement) {
	sp.move(playerMovement * speed, 0);
}
