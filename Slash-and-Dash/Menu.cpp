#include "Menu.h"

Menu::Menu(float width, float height) : currentIndex(0), currentState(MainMenu) {
    if (!font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf")) {
    }
    bg.loadFromFile("Assets/Texture/menu/menu-background.png");
    bg_shape.setTexture(&bg);
    bg_shape.setSize((sf::Vector2f)bg.getSize()*5.f);
    mainMenuTextures[0].loadFromFile("assets/Texture/menu/menu-play-hover.png");
    mainMenuTextures[1].loadFromFile("assets/Texture/menu/menu-options-hover.png");
    mainMenuTextures[2].loadFromFile("assets/Texture/menu/menu-exit-hover.png");
    button_hover.setTexture(&mainMenuTextures[0]);
    button_hover.setSize((sf::Vector2f)button_hover.getTexture()->getSize()*2.f);
    setState(MainMenu, { static_cast<unsigned int>(width), static_cast<unsigned int>(height) });

    button_hover.setOrigin(button_hover.getSize() / 2.f);
}

void Menu::moveUp() {
    if (currentState == MenuState::MainMenu) {
        currentIndex = (currentIndex - 1 + menuOptions.size()) % menuOptions.size();
        button_hover.setTexture(&mainMenuTextures[currentIndex]);
    }else{
        updateOptionColor(currentIndex, sf::Color::White);
        currentIndex = (currentIndex - 1 + menuOptions.size()) % menuOptions.size();
        updateOptionColor(currentIndex, sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (currentState == MenuState::MainMenu) {
        currentIndex = (currentIndex + 1) % menuOptions.size();
        button_hover.setTexture(&mainMenuTextures[currentIndex]);
    }
    else {
        updateOptionColor(currentIndex, sf::Color::White);
        currentIndex = (currentIndex + 1) % menuOptions.size();
        updateOptionColor(currentIndex, sf::Color::Red);
    }
}

int Menu::getSelectedOption() const {
    return currentIndex;
}

void Menu::resetCurrentIndex() {
    currentIndex = 0;
    button_hover.setTexture(&mainMenuTextures[0]);
}

void Menu::updateOptionColor(int index, const sf::Color& color) {
    menuOptions[index].setFillColor(color);
}

void Menu::render(sf::RenderTarget* target) {
    button_hover.setPosition(sf::Vector2f(target->getSize().x / 2, target->getSize().y / 2));
    target->setView(target->getDefaultView());
    target->draw(bg_shape);
    if (currentState == MenuState::MainMenu) {
        target->draw(button_hover);
    }else{
        for (const auto& option : menuOptions) {
            target->draw(option);
        }
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

std::vector<int> Menu::getSelectetResolution(int x) {
    switch (x) {
    case 0:
        return std::vector<int>{640, 360};
        break;
    case 1:
        return std::vector<int>{854, 480};
        break;
    case 2:
        return std::vector<int>{1280, 720};
        break;
    case 3:
        return std::vector<int>{1920, 1080};
        break;
    case 4:
        return std::vector<int>{2560, 1440};
        break;
    case 5:
        return std::vector<int>{3840, 2160};
        break;

    default:
        return std::vector<int>{960, 540};
    }
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
