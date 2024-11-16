#include "Menu.h"

Menu::Menu(float width, float height) : currentIndex(0), currentState(MainMenu) {
    if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
        
    }
    loadMainMenu();
}

void Menu::moveUp() {
    updateOptionColor(currentIndex, sf::Color::White);
    currentIndex = (currentIndex - 1 + menuOptions.size()) % menuOptions.size();
    updateOptionColor(currentIndex, sf::Color::Red);
}

void Menu::moveDown() {
    updateOptionColor(currentIndex, sf::Color::White);
    currentIndex = (currentIndex + 1) % menuOptions.size();
    updateOptionColor(currentIndex, sf::Color::Red);
}

int Menu::getSelectedOption() const {
    return currentIndex;
}

void Menu::updateOptionColor(int currentIndex, const sf::Color& color) {
    menuOptions[currentIndex].setFillColor(color);
}

void Menu::render(sf::RenderTarget* target) {
    for (const auto& option : menuOptions) {
        target->draw(option);
    }
}

void Menu::setState(MenuState newState) {
    currentState = newState;
    currentIndex = 0;

    switch (newState) {
    case MainMenu:
        loadMainMenu();
        break;
    case SettingsMenu:
        loadSettingsMenu();
        break;
    case SoundMenu:
        loadSoundMenu();
        break;
    case DisplayMenu:
        loadDisplayMenu();
        break;
    }
}

Menu::MenuState Menu::getState() const {
    return currentState;
}

void Menu::loadMainMenu() {
    menuOptions.clear();

    std::vector<std::string> options = { "Play", "Settings", "Quit" };
    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(400, 200 + i * 50));

        text.setCharacterSize(24);
        menuOptions.push_back(text);
    }
}

void Menu::loadSettingsMenu() {
    menuOptions.clear();

    std::vector<std::string> options = { "Sound", "Display", "Back" };
    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(400, 200 + i * 50));

        text.setCharacterSize(24);
        menuOptions.push_back(text);
    }
}

void Menu::loadSoundMenu() {
    menuOptions.clear();

    std::vector<std::string> options = { "On", "Off", "Back" };
    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(400, 200 + i * 50));

        text.setCharacterSize(24);
        menuOptions.push_back(text);
    }
}

void Menu::loadDisplayMenu() {
    menuOptions.clear();

    std::vector<std::string> options = { "Toggle Fullscreen", "Resolution", "Back" };
    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(400, 200 + i * 50));

        text.setCharacterSize(24);
        menuOptions.push_back(text);
    }
}