#include "Menu.h"

Menu::Menu(float width, float height) : selectedOptionIndex(0) {
    // Load a font (make sure you have this file, or adjust the path)
    if (!font.loadFromFile("path/to/font.ttf")) {
        // Handle error
    }

    // Menu options
    std::vector<std::string> options = { "Play", "Settings", "Quit" };

    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White); // Highlight first option
        text.setPosition(sf::Vector2f(width / 2, height / (options.size() + 1) * (i + 1)));

        menuOptions.push_back(text);
    }
}

void Menu::moveUp() {
    if (selectedOptionIndex - 1 >= 0) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White); // Deselect current
        selectedOptionIndex--;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);   // Select new
    }
}

void Menu::moveDown() {
    if (selectedOptionIndex + 1 < menuOptions.size()) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White); // Deselect current
        selectedOptionIndex++;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);   // Select new
    }
}

int Menu::getSelectedOption() const {
    return selectedOptionIndex;
}

void Menu::render(sf::RenderTarget* target) {
    for (const auto& option : menuOptions) {
        target->draw(option);
    }
}
