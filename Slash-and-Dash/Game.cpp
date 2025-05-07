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

	// Reset Controller Flags
	player1AttackPressed = false;
	player2AttackPressed = false;
	menuConfirmPressed = false;
	menuBackPressed = false;


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

	player->update(deltaTime); // Beinhaltet Player::handleInput fur Bewegung
	player2->update(deltaTime);

	sf::Vector2f currentPos1 = player->get_Position();
	sf::Vector2f currentPos2 = player2->get_Position();
	sf::Vector2f currentAveragePosition = (currentPos1 + currentPos2) * 0.5f;

	sf::Vector2f movement = currentAveragePosition - prevAveragePosition;
	sf::Vector2f movement1 = currentPos1 - prevPos1;
	sf::Vector2f movement2 = currentPos2 - prevPos2;

	float directionDot = movement1.x * movement2.x + movement1.y * movement2.y;

	world->update(directionDot > 0 ? movement.x : 0);

	// --- Angriff durch Spieler 1 (Controller oder Maus) ---
	// ALT: if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->is_alive) {
	if ((player1AttackPressed || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && player->is_alive) {
		player1AttackPressed = false; // Flag sofort zurucksetzen
		player->attack();
		if (player->get_attackBounds().intersects(player2->get_globalBounds()) && player->get_sword_position() != player2->get_sword_position()) {
			player2->die();
			die.play();
			alive = false; // Spielzustand andern (wird im Haupt-Update gepruft)
			player1_won = true; // Merken wer gewonnen hat
			if (countPoints) {
				points[0]++;
				std::cout << "Player 0: " << points[0] << std::endl;
				countPoints = false; // Punkte nur einmal pro Runde zahlen
			}
			// Endscreen startet nur, wenn nicht bereits ein Gewinn-Screen lauft
			if (!bool_start_winning_screen) endscreen->endscreen_start(1.4, 4, 0);
		}
	}
	else if (player2->is_dying_animation_finished() && endscreen->is_finished() && !bool_start_winning_screen) {
		// Runde neu starten, wenn Spieler 2 gestorben ist und Endscreen fertig
		start_Round();
		countPoints = true; // Punkte zahlen wieder erlauben
		player1_won = false;
		alive = true; // Spielzustand wiederherstellen
	}

	// --- Angriff durch Spieler 2 (Controller oder Maus) ---
	// ALT: if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && player2->is_alive) {
	if ((player2AttackPressed || sf::Mouse::isButtonPressed(sf::Mouse::Right)) && player2->is_alive) {
		player2AttackPressed = false; // Flag sofort zurucksetzen
		player2->attack();
		if (player2->get_attackBounds().intersects(player->get_globalBounds()) && player->get_sword_position() != player2->get_sword_position()) {
			player->die();
			die.play();
			alive = false; // Spielzustand andern
			player1_won = false; // Spieler 2 hat diese Runde gewonnen
			if (countPoints) {
				points[1]++;
				std::cout << "Player 1: " << points[1] << std::endl;
				countPoints = false; // Punkte nur einmal pro Runde zahlen
			}
			// Endscreen startet nur, wenn nicht bereits ein Gewinn-Screen lauft
			if (!bool_start_winning_screen) endscreen->endscreen_start(1.4, 4, 1);
		}
	}
	else if (player->is_dying_animation_finished() && endscreen->is_finished() && !bool_start_winning_screen) {
		// Runde neu starten, wenn Spieler 1 gestorben ist und Endscreen fertig
		start_Round();
		countPoints = true; // Punkte zahlen wieder erlauben
		alive = true; // Spielzustand wiederherstellen
	}
}

void Game::update(sf::Time deltaTime) {
	updatePollEvents();

	if (state == State::inGameMenu || state == State::inMainMenu) {
		updateMenu();
	}
	else if (state == State::Playing) {
		updatePlayer(deltaTime);
	}

	if (!alive || bool_start_winning_screen) {
		int winner = player1_won ? 0 : 1;
		endscreen->update(winner);
	}

	end_game();
}

void Game::updateMenu() {

	// --- Men--Navigation (Polling mit Verz-gerung) ---
	bool navigated = false; // Um Mehrfachnavigation pro Frame zu verhindern
	if (menuNavClock.getElapsedTime() > menuNavDelay) {
		for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
			if (sf::Joystick::isConnected(i)) {
				// D-Pad Y-Achse (oft invertiert: oben = positiv)
				float povY = sf::Joystick::getAxisPosition(i, sf::Joystick::PovY);
				// Linker Stick Y-Achse (normal: oben = negativ)
				float stickY = sf::Joystick::getAxisPosition(i, sf::Joystick::Y);

				// Schwellenwerte prufen
				if (povY > 50 || stickY < -50) { // Nach oben
					menu->moveUp();
					menuNavClock.restart(); // Timer zurucksetzen
					navigated = true;
					break; // Nur Input von einem Controller pro Frame
				}
				else if (povY < -50 || stickY > 50) { // Nach unten
					menu->moveDown();
					menuNavClock.restart(); // Timer zurucksetzen
					navigated = true;
					break; // Nur Input von einem Controller pro Frame
				}
				// Optional: Hier PovX / X fur Links/Rechts hinzuf-gen, falls benotigt
			}
		}
	}

	// --- Men- Aktionen (Bestatigen / Zuruck via Flags) ---
	if (menuConfirmPressed) {
		menuConfirmPressed = false; // Flag zurucksetzen
		handleMenuSelection();
	}
	else if (menuBackPressed) {
		menuBackPressed = false; // Flag zur-cksetzen
		handleMenuBack();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !navigated) {
		menu->moveUp();
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)); // Verhindert Halten
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !navigated) {
		menu->moveDown();
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)); // Verhindert Halten
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		 handleMenuSelection();
		 while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)); // Verhindert Halten
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // Wird bereits in pollEvents behandelt
		 handleMenuBack();
		 while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	}
}

void Game::updatePollEvents() {
	// Flags fur diesen Frame zurucksetzen (f-r gedr-ckte Tasten wie bei Keyboard)
	// Angriff/Menu wird nur einmal pro Druck ausgel-st, daher kein Reset hier n-tig.

	while (window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			window->close();
		}

		// --- Tastatur Events ---
		if (e.type == sf::Event::KeyPressed) {
			if (e.key.code == sf::Keyboard::Escape) {
				if (state == State::Playing) {
					state = State::inGameMenu;
					menu->setState(Menu::MainMenu, window->getSize()); // Gehe zum Hauptmen- im Pause-Modus
					menu->resetCurrentIndex();
				}
				else if (state == State::inGameMenu || state == State::inMainMenu) {
					// Handle "Zuruck" im Menu durch Escape
					handleMenuBack();
				}
			}
			// Tastatur-Menusteuerung (wird in updateMenu behandelt, falls gew-nscht)
			if ((state == State::inGameMenu || state == State::inMainMenu)) {
				if (e.key.code == sf::Keyboard::W) menu->moveUp();
				else if (e.key.code == sf::Keyboard::S) menu->moveDown();
				else if (e.key.code == sf::Keyboard::Enter) handleMenuSelection();
			}
		}

		// --- Fenster Events ---
		if (e.type == sf::Event::Resized) {
			sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
			updateView();
			// Menu an neue Groese anpassen, falls im Menu
			if (state == State::inGameMenu || state == State::inMainMenu) {
				menu->setState(menu->getState(), window->getSize()); // Aktuellen Men-status neu laden mit neuer Gr--e
			}
		}

		// --- Controller Connect / Disconnect Events ---
		if (e.type == sf::Event::JoystickConnected) {
			std::cout << "Controller verbunden: " << e.joystickConnect.joystickId << std::endl;
		}
		if (e.type == sf::Event::JoystickDisconnected) {
			std::cout << "Controller getrennt: " << e.joystickConnect.joystickId << std::endl;
			// Hier konnte man Logik hinzufugen, z.B. Spiel pausieren
		}

		// --- Controller Button Events ---
		if (e.type == sf::Event::JoystickButtonPressed) {
			unsigned int joystickId = e.joystickButton.joystickId;
			unsigned int button = e.joystickButton.button;

			// Angriff (nur im Spielzustand)
			if (state == State::Playing) {
				if (joystickId == player->getJoystickID() && button == 0) { // Annahme: Button 0 = Angriff P1
					player1AttackPressed = true;
				}
				else if (joystickId == player2->getJoystickID() && button == 0) { // Annahme: Button 0 = Angriff P2
					player2AttackPressed = true;
				}
			}

			// Menu Interaktion (nur im Menuzustand)
			if (state == State::inGameMenu || state == State::inMainMenu) {
				if (button == 0) { // Annahme: Button 0 = Bestatigen
					menuConfirmPressed = true;
				}
				else if (button == 1) { // Annahme: Button 1 = Zuruck
					menuBackPressed = true;
				}
			}
		}
		// Optional: JoystickButtonReleased Event verarbeiten, falls benotigt
	}

	// Debug Menu Update (ausserhalb der Schleife, wird jeden Frame gemacht)
	if (enable_debug_menu) debug_menu->update(player, player2);
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

void Game::handleMenuSelection() {
	int selectedOption = menu->getSelectedOption();
	sf::Vector2u windowSize = window->getSize();

	switch (menu->getState()) {
	case Menu::MainMenu:
		if (selectedOption == 0) {
			state = State::Playing;
			// Eventuell hier das Menu ausblenden
		}
		else if (selectedOption == 1) {
			menu->setState(Menu::SettingsMenu, windowSize);
		}
		else if (selectedOption == 2) {
			window->close();
		}
		break;

	case Menu::SettingsMenu:
		if (selectedOption == 0) menu->setState(Menu::SoundMenu, windowSize);
		else if (selectedOption == 1) menu->setState(Menu::DisplayMenu, windowSize);
		else if (selectedOption == 2) menu->setState(Menu::MainMenu, windowSize);
		break;

	case Menu::SoundMenu:
		if (selectedOption == 0) mBg.play();
		if (selectedOption == 1) mBg.pause();
		if (selectedOption == 2) menu->setState(Menu::SettingsMenu, windowSize);
		break;

	case Menu::DisplayMenu:
		if (selectedOption == 0) {
			fullscreen = !fullscreen;
			window->create(sf::VideoMode(960, 540), "Slash & Dash", fullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Titlebar);
			updateView();
			menu->setState(Menu::DisplayMenu, window->getSize());
		}
		else if (selectedOption == 1) {
			menu->setState(Menu::ResolutionMenu, windowSize);
		}
		else if (selectedOption == 2) {
			menu->setState(Menu::SettingsMenu, windowSize);
		}
		break;

	case Menu::ResolutionMenu:
	{
		std::vector<int> res = menu->getSelectetResolution(selectedOption);
		window->create(sf::VideoMode(res[0], res[1]), "Slash & Dash", fullscreen ? sf::Style::Fullscreen : sf::Style::Close | sf::Style::Titlebar);
		updateView(); // Wichtig!
		menu->setState(Menu::ResolutionMenu, window->getSize());
	}
	break;
	}
	// menu->resetCurrentIndex();
}

void Game::handleMenuBack() {
	sf::Vector2u windowSize = window->getSize();
	switch (menu->getState()) {
		// Von Untermenus zuruck zum ubergeordneten Menu
	case Menu::SettingsMenu:
	case Menu::SoundMenu:
	case Menu::DisplayMenu:
	case Menu::ResolutionMenu:
		menu->setState(Menu::SettingsMenu, windowSize);
		break;

	case Menu::MainMenu:
		if (state == State::inGameMenu) {
			state = State::Playing;
		}
		break;
	default:
		break;
	}
	// menu->resetCurrentIndex();
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