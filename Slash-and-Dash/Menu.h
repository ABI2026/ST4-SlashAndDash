#pragma once
#include "SFML/Graphics.hpp"

class Menu {
public:
    enum MenuState {
        MainMenu,
        SettingsMenu,
        SoundMenu,
        DisplayMenu
    };

    Menu(float width, float height);

    void moveUp();
    void moveDown();
    int getSelectedOption() const;

    void updateOptionColor(int index, const sf::Color& color);

    void render(sf::RenderTarget* target);

    void setState(MenuState newState);
    MenuState getState() const;

    void loadMainMenu();
    void loadSettingsMenu();
    void loadSoundMenu();
    void loadDisplayMenu();

private:
    std::vector<sf::Text> menuOptions;
    sf::Font font;
    int currentIndex;

    MenuState currentState;
};
