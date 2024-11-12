#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu(float width, float height);
    void moveUp();
    void moveDown();
    int getSelectedOption() const;

    void updateOptionColor(int index, const sf::Color& color);

    void render(sf::RenderTarget *target);

private:
    std::vector<sf::Text> menuOptions;
    sf::Font font;
    int Index;
};