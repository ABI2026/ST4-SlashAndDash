#include "Game.h"


Game::Game() {
	viewWidth = 960;
	viewHeight = 540;
	init();
}

void Game::run() {
	sf::Clock clock;
	while (this->window->isOpen()) {
		sf::Time deltaTime = clock.restart();

		if(toMainMenu) start_game();
		update(deltaTime);
		render();
	}
}

void Game::init() {
	initWinow();
	initVars();
	initPlayer();
	initEndscreen();
}

void Game::initWinow() {
	window = new sf::RenderWindow(sf::VideoMode(960, 540), "Slash & Dash", sf::Style::Close);

	gameView.setSize(viewWidth, viewHeight);
	gameView.setCenter(viewWidth / 2, viewHeight / 2);
	updateView();
	window->setVerticalSyncEnabled(true);

	this->debug_menu = new Debug_Menu();
}

void Game::initVars() {
	state = State::inMainMenu;
	fullscreen = false;
	this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
	world = new World;
	alive = true;
	countPoints = true;
	player1_won = false;
	toMainMenu = false;
	bool_start_winning_screen = false;
	enable_debug_menu = true;

	mBg.openFromFile("assets/Music/Slash and Dash idea 1.wav");
	mBg.setVolume(10);
	mBg.play();
	mBg.setLoop(true);

	die_buffer.loadFromFile("assets/Sounds/dying.wav");
	die.setBuffer(die_buffer);
	die.setLoop(false);
}

void Game::initPlayer() {
	this->player = new Player(0);
	this->player2 = new Player(1);
	this->player2->setPosition(900, 140);
}

void Game::initEndscreen() {

	this->endscreen = new Endscreen(); 
}

void Game::updateView() {
	// aspect ratio of the window
	float windowRatio = float(window->getSize().x) / float(window->getSize().y);
	float viewRatio = 16.f / 9.f;

	float sizeX = 1.f;
	float sizeY = 1.f;
	float posX = 0.f;
	float posY = 0.f;

	// Adjust the viewport size and position based on the aspect ratios
	if (windowRatio > viewRatio) {
		// Window is wider than the view
		sizeX = viewRatio / windowRatio;
		posX = (1.f - sizeX) / 2.f;
	}
	else {
		// Window is taller than the view
		sizeY = windowRatio / viewRatio;
		posY = (1.f - sizeY) / 2.f;
	}

	// Set the viewport of the game view; posX und posY = oben links
	gameView.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void Game::updatePlayer(sf::Time deltaTime) {
	sf::Vector2f prevPos1 = player->get_Position();
	sf::Vector2f prevPos2 = player2->get_Position();
	sf::Vector2f prevAveragePosition = (prevPos1 + prevPos2) * 0.5f;

	player->update(deltaTime);
	player2->update(deltaTime);

	sf::Vector2f currentPos1 = player->get_Position();
	sf::Vector2f currentPos2 = player2->get_Position();
	sf::Vector2f currentAveragePosition = (currentPos1 + currentPos2) * 0.5f;

	sf::Vector2f movement = currentAveragePosition - prevAveragePosition;
	sf::Vector2f movement1 = currentPos1 - prevPos1;
	sf::Vector2f movement2 = currentPos2 - prevPos2;

	float directionDot = movement1.x * movement2.x + movement1.y * movement2.y;

	world->update(directionDot > 0 ? movement.x : 0);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->is_alive) {
		player->attack();
		if (player->get_attackBounds().intersects(player2->get_globalBounds())) {
			player2->die();
			die.play();
			alive = false;
			player1_won = true;
			if (countPoints) {
				points[0] += 1;
				cout << "Player 0: " << points[0] << endl;
				countPoints = false;
			}
			if(!bool_start_winning_screen) endscreen->endscreen_start(1.4, 4, 0);
		}
	}
	else if (player2->is_dying_animation_finished() && endscreen->is_finished() && !bool_start_winning_screen) {
		start_Round();
		countPoints = true;
		player1_won = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && player2->is_alive) {
		player2->attack();
		if (player2->get_attackBounds().intersects(player->get_globalBounds())) {
			player->die();
			die.play();
			alive = false;
			if (countPoints) {
				points[1]++;
				cout << "Player 1:" << points[1] << endl;
				countPoints = false;
			}
			if(!bool_start_winning_screen)endscreen->endscreen_start(1.4, 4, 1);
		}
	}
	else if (player->is_dying_animation_finished() && endscreen->is_finished() && !bool_start_winning_screen) {
		start_Round();
		countPoints = true;
	}
}

void Game::update(sf::Time deltaTime) {
	updatePollEvents();
	if (state == State::inGameMenu || state == State::inMainMenu) updateMenu(); else updatePlayer(deltaTime);
	if (!alive && !toMainMenu && player1_won) { 
		endscreen->update(0); 
	}
	else if (!alive && !toMainMenu && !player1_won) endscreen->update(1);
	end_game();
}

void Game::updateMenu() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		int selectedOption = menu->getSelectedOption();

		switch (menu->getState()) {
		case Menu::MainMenu:
			if (selectedOption == 0) {
				state = State::Playing;
			}
			if (selectedOption == 1) menu->setState(Menu::SettingsMenu, window->getSize());
			else if (selectedOption == 2) window->close();
			break;

		case Menu::SettingsMenu:
			if (selectedOption == 0) menu->setState(Menu::SoundMenu, window->getSize());
			else if (selectedOption == 1) menu->setState(Menu::DisplayMenu, window->getSize());
			else if (selectedOption == 2) menu->setState(Menu::MainMenu, window->getSize());
			break;

		case Menu::SoundMenu:
			if (selectedOption == 0) mBg.play();
			if (selectedOption == 1) mBg.pause();
			if (selectedOption == 2) menu->setState(Menu::SettingsMenu, window->getSize());
			break;
		case Menu::DisplayMenu:
			if (selectedOption == 0) {
				fullscreen = !fullscreen;
				window->create(sf::VideoMode(960, 540),
					"Slash & Dash", fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
				updateView();
				menu->setState(Menu::DisplayMenu, window->getSize());
			}
			if (selectedOption == 1) menu->setState(Menu::ResolutionMenu, window->getSize());
			if (selectedOption == 2) menu->setState(Menu::SettingsMenu, window->getSize());
			break;
		case Menu::ResolutionMenu:
			std::vector<int> res = menu->getSelectetResolution(selectedOption);
			window->create(sf::VideoMode(res[0], res[1]), "Slash & Dash", fullscreen ? sf::Style::Fullscreen : sf::Style::Close);
			menu->setState(Menu::ResolutionMenu, window->getSize());
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		menu->setState(Menu::MainMenu, window->getSize());
	}
}

void Game::updatePollEvents() {

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window->close();
		}
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
			if (state == State::Playing) {
				state = State::inGameMenu;
			}
			else if (state == State::inGameMenu) {
				menu->resetCurrentIndex();
				state = State::Playing;
			}
		}
		if (e.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
			updateView();
		}
	}
	if (enable_debug_menu)debug_menu->update(player, player2);
}

void Game::start_game()
{
	initVars();
	initPlayer();
	initEndscreen();
}

void Game::start_Round() {
	initPlayer();
	//initWorld();
}

void Game::end_game()
{
	if (points[0] == 3) {
		if (!endscreen->getWinning_screen_started()) {
			bool_start_winning_screen = true;
			endscreen->start_winning_screen(1.4, 4, 0);
		}
		if (endscreen->is_finished()) {
			toMainMenu = true;
			player1_won = false;
			state = State::inMainMenu();
			points[0] = 0;
		}
	}
	else if (points[1] == 3) {
		if (!endscreen->getWinning_screen_started()) {
			bool_start_winning_screen = true;
			endscreen->start_winning_screen(1.4, 4, 1);
		}
		if (endscreen->is_finished()) {
			toMainMenu = true;
			player1_won = false;
			state = State::inMainMenu();
			points[1] = 0;
		}
	}
}

void Game::render() {
	window->clear();
	window->setView(gameView);
	if (state == State::Playing) {
		world->render(this->window);
		player->render(this->window);
		player2->render(this->window);
	}
	else if (state == State::inGameMenu || state == State::inMainMenu) {
		menu->render(this->window);
	}

	if (!alive) {
		endscreen->render(this->window);
	}
	if(enable_debug_menu)debug_menu->render(this->window);

	window->display();
}

Game::~Game() {
	delete this->window;
	delete this->player;
	delete this->world;
}