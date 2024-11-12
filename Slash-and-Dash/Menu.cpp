#include "Menu.h"

Menu::Menu(float width, float height) : selectedOptionIndex(0) {
    if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
        
    }

    std::vector<std::string> options = { "Play", "Settings", "Quit" };

    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(width / 2, height / (options.size() + 1) * (i + 1)));

        menuOptions.push_back(text);
    }
}

void Menu::moveUp() {
    if (selectedOptionIndex - 1 >= 0) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);
        selectedOptionIndex--;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedOptionIndex + 1 < menuOptions.size()) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);
        selectedOptionIndex++;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedOption() const {
    return selectedOptionIndex;
}

void Menu::render(sf::RenderTarget* target) {
    for (sf::Text option : menuOptions) {
        target->draw(option);
    }
}
