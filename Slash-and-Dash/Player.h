#pragma once
#include <SFML/Graphics.hpp>
class Player
{
private:
	sf::Texture tx;
	sf::Sprite sp;
	std::vector<sf::Texture> playerTextures;

public:
	Player(int index);
	~Player();

	sf::FloatRect getBounds();

	void render(sf::RenderTarget* target);

};

