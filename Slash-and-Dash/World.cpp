#include "World.h"

World::World() {
	tx.loadFromFile("Assets/Texture/lvl1_layer3.png");
	sp.setTexture(tx);
	loadLvl();

	setRandomLevel();
}


World::~World() {
	for (auto& lvl : level) {
		for (auto& layer : lvl) {
			delete layer;
		}
	}
}

void World::loadLvl() {
	//!lvl 1
	std::vector<Layer*> lvl1;
	std::vector<Layer*> lvl2;

	lvl1.push_back(new Layer("assets/Texture/lvl1_layer3.png", 1.f, 3));
	lvl1.push_back(new Layer("assets/Texture/lvl1_layer2.png", 0.3, 2));
	//lvl1.push_back(new Layer("assets/Texture/nebel1.png", 0, 1));
	lvl1.push_back(new Layer("assets/Texture/lvl1_layer1.png", 0.4, 1));
	this->level.push_back(lvl1);

	//!lvl 2
	lvl2.push_back(new Layer("assets/Texture/lvl2_layer3.png", 1.f, 3));
	lvl2.push_back(new Layer("assets/Texture/lvl2_layer2.png", 0.3, 2));
	//lvl1.push_back(new Layer("assets/Texture/nebel1.png", 0, 1));
	lvl2.push_back(new Layer("assets/Texture/lvl2_layer1.png", 0.4, 1));
	this->level.push_back(lvl2);
}

void World::setRandomLevel() {
	if (!level.empty()) {
		std::srand(static_cast<unsigned>(std::time(nullptr)));
		int randomIndex = std::rand() % level.size();
		setLvl(randomIndex);
	}
}


void World::setLvl(int index) {
	if (index >= 0 && index < level.size()) {
		lvlIndex = index;
	}
}

void World::update(float playerMovement) {
	for (Layer* layer : level[lvlIndex]) {
		layer->update(playerMovement);
	}
}

void World::render(sf::RenderTarget* target) {
	for (Layer* layer : level[lvlIndex]) {
		target->draw(layer->sp);
	}
}
