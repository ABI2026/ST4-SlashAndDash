#include "Game.h"
#include "Player.h"

Game::Game() {
	viewWidth = 960;
	viewHeight = 540;
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
	window = new sf::RenderWindow(sf::VideoMode(960, 540), "Slash & Dash", sf::Style::Default);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(true);

	gameView.setSize(viewWidth, viewHeight);
	gameView.setCenter(viewWidth / 2, viewHeight / 2);
	updateView();
}

void Game::initVars() {
	state = 0;
	fullscreen = false;
	this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);

	world = new World;
}

void Game::initPlayer()
{
	Player();
}

void Game::updateView() {
	float windowRatio = float(window->getSize().x) / float(window->getSize().y);
	float viewRatio = viewWidth / viewHeight;

	float sizeX = 1.f;
	float sizeY = 1.f;
	float posX = 0.f;
	float posY = 0.f;

	if (windowRatio > viewRatio) {
		sizeX = viewRatio / windowRatio;
		posX = (1.f - sizeX) / 2.f;
	}
	else {
		sizeY = windowRatio / viewRatio;
		posY = (1.f - sizeY) / 2.f;
	}

	gameView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void Game::updatePlayer()
{

}

void Game::update(){
	updatePollEvents();

	if (!state) updateMenu();
}

void Game::updateMenu() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        int selectedOption = menu->getSelectedOption();

        switch (menu->getState()) {
        case Menu::MainMenu:
            if (selectedOption == 1) menu->setState(Menu::SettingsMenu);
            else if (selectedOption == 2) window->close();
            break;

        case Menu::SettingsMenu:
            if (selectedOption == 0) menu->setState(Menu::SoundMenu);
            else if (selectedOption == 1) menu->setState(Menu::DisplayMenu);
            else if (selectedOption == 2) menu->setState(Menu::MainMenu);
            break;

        case Menu::SoundMenu:
			if (selectedOption == 2) menu->setState(Menu::SettingsMenu);
			break;
        case Menu::DisplayMenu:
			if (selectedOption == 0) {
				fullscreen = !fullscreen;
				window->create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),
					"Slash & Dash", fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
				updateView();
			}
            if (selectedOption == 2) menu->setState(Menu::SettingsMenu);
            break;
        }
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        menu->moveUp();
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        menu->moveDown();
        while (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
    }
}

void Game::updatePollEvents(){
	
	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window->close();
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			state ^= 1;
		}
		if (e.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
			updateView();
		}
	}
}

void Game::render() {
	window->clear();

	window->setView(gameView);
	world->render(this->window);

	if (!state) {
		window->setView(window->getDefaultView());
		menu->render(this->window);
	}

	window->display();
}

sf::Event Game::getEvent() {
	return e;
}