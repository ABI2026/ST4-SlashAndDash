#include "Game.h"
#include "Player.h"

Game::Game() {
	init();
}

Game::~Game(){
	delete this->window;
}

void Game::run(){
	while (this->window->isOpen()) {
		update();
		render();
	}
}

void Game::init(){
	initWinow();
	initVars();
}

void Game::initWinow(){
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Slash & Dash", sf::Style::Close);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(true);
}

void Game::initVars() {
	inMenu = false;
	this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
}

void Game::update(){
	updatePollEvents();

	if (inMenu) updateMenu();
}

void Game::updateMenu() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		menu->moveUp();
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		menu->moveDown();
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
	}
}

void Game::updatePollEvents(){
	sf::Event e;
	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window->close();
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			inMenu = !inMenu;
		}
	}
}

void Game::render(){
	window->clear();

	if (inMenu) menu->render(this->window);

	window->display();
}
