#include "Game.h"
#include "Player.h"

Game::Game() {
	init();
}

Game::~Game(){

}

void Game::run(){
	while (this->window->isOpen()) {
		update();
		render();
	}
}

void Game::init(){
	initWinow();
}

void Game::initWinow(){
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Slash & Dash", sf::Style::Close);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(true);
}

void Game::update(){
	updatePollEvents();
}

void Game::updatePollEvents(){
	sf::Event e;
	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window->close();
		}
	}
}

void Game::render(){
	window->clear();

	window->display();
}
