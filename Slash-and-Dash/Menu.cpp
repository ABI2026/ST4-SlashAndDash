#include "Menu.h"

Menu::Menu(float width, float height) : Index(0) {
    if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {

    }

    std::vector<std::string> options = { "Play", "Settings", "Quit" };

    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(width/2 - 40, height / (options.size() + 1) * (i + 1) - 20));

        menuOptions.push_back(text);
    }
}

void Menu::moveUp() {
    updateOptionColor(Index, sf::Color::White);
    Index = (Index - 1 + menuOptions.size()) % menuOptions.size(); // damit das wieder nach oben geht wenn ganz unten & andersrum
    updateOptionColor(Index, sf::Color::Red);
}

void Menu::moveDown() {
    updateOptionColor(Index, sf::Color::White);
    Index = (Index + 1) % menuOptions.size(); //wie da oben
    updateOptionColor(Index, sf::Color::Red);
}

void Menu::updateOptionColor(int index, const sf::Color& color) {
    menuOptions[index].setFillColor(color);
}

void Menu::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && Index == 2) {

    }
}

int Menu::getSelectedOption() const {
    return Index;
}

void Menu::render(sf::RenderTarget* target) {
    for (const auto& option : menuOptions) {
        target->draw(option);
    }
}
