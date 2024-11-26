#include "Menu.h"

Menu::Menu(float width, float height) : currentIndex(0), currentState(MainMenu) {
    if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
    }
    setState(MainMenu, { static_cast<unsigned int>(width), static_cast<unsigned int>(height) });
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

void Menu::updateOptionColor(int index, const sf::Color& color) {
    menuOptions[index].setFillColor(color);
}

void Menu::render(sf::RenderTarget* target) {
    for (const auto& option : menuOptions) {
        target->draw(option);
    }
}

void Menu::setState(MenuState newState, sf::Vector2u ws) {
    currentState = newState;
    currentIndex = 0;
    int cs = ws.y / 20;
    switch (newState) {
    case MainMenu:
        loadMainMenu(cs, ws);
        break;
    case SettingsMenu:
        loadSettingsMenu(cs, ws);
        break;
    case SoundMenu:
        loadSoundMenu(cs, ws);
        break;
    case DisplayMenu:
        loadDisplayMenu(cs, ws);
        break;
    case ResolutionMenu:
        loadResolutionMenu(cs, ws);
        break;
    }
}

Menu::MenuState Menu::getState() const {
    return currentState;
}

void Menu::loadMenuOptions(const std::vector<std::string>& options, int cs, sf::Vector2u ws) {
    menuOptions.clear();

    float verticalSpacing = ws.y * 0.05;
    float startY = ws.y * 0.3;

    for (std::size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(sf::Vector2f(ws.x * 0.1, startY + i * verticalSpacing));
        text.setCharacterSize(cs);
        menuOptions.push_back(text);
    }
}

void Menu::loadMainMenu(int cs, sf::Vector2u ws) {
    std::vector<std::string> options = { "Play", "Settings", "Quit" };
    loadMenuOptions(options, cs, ws);
}

void Menu::loadSettingsMenu(int cs, sf::Vector2u ws) {
    std::vector<std::string> options = { "Sound", "Display", "Back" };
    loadMenuOptions(options, cs, ws);
}

void Menu::loadSoundMenu(int cs, sf::Vector2u ws) {
    std::vector<std::string> options = { "On", "Off", "Back" };
    loadMenuOptions(options, cs, ws);
}

void Menu::loadDisplayMenu(int cs, sf::Vector2u ws) {
    std::vector<std::string> options = { "Toggle Fullscreen", "Resolution", "Back" };
    loadMenuOptions(options, cs, ws);
}

void Menu::loadResolutionMenu(int cs, sf::Vector2u ws) {
    std::vector<std::string> options = { "640 x 360", "854 x 480", "1280 x 720", "1920 x 1080", "2560 x 1440", "3840 x 2160"};
    loadMenuOptions(options, cs, ws);
}
