#include "Player.h"

Player::Player(int index)
{
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

void Player::render(sf::RenderTarget* target){
	target->draw(sp);
}


