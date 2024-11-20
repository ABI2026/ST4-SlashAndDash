#include "Player.h"
#include <iostream>

Player::Player(int index)
{
	this->index = index;
	if (index < playerTextures.size()) {
		tx = playerTextures[index];
		sp.setTexture(tx);
	}
	sp.setPosition(50.0f, 600.0f);
	sp.setScale(0.5f, 0.5f);
}

Player::~Player() {}

sf::FloatRect Player::getBounds()
{
	return sp.getGlobalBounds();
}

void Player::addTexture(std::string file)
{
	if (!tx.loadFromFile(file)) {
		std::cout << "One Playertexture was not load corectly" << std::endl;
		return;
	}
	playerTextures.push_back(tx);
}

void Player::switchTexture(int index)
{
	sp.setTexture(playerTextures[index]);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
		index++;
	}

	if (game.getEvent().type == sf::Event::TextEntered)
	{
		if (game.getEvent().text.unicode == 0x00DC) {
			index--;
		}
	}
}

void Player::render(sf::RenderTarget* target){
	target->draw(sp);
}

void Player::movePlayer1()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sp.move(-1.0, 0.0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sp.move(1.0, 0.0);
	}
}

void Player::movePlayer2()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sp.move(-1.0, 0.0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		sp.move(1.0, 0.0);
	}
}

