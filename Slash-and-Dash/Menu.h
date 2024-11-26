#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

class Menu {
public:
    enum MenuState {
        MainMenu,
        SettingsMenu,
        SoundMenu,
        DisplayMenu,
        ResolutionMenu
    };

    Menu(float width, float height);

    void moveUp();
    void moveDown();
    int getSelectedOption() const;

    void updateOptionColor(int index, const sf::Color& color);

    void setState(MenuState newState, sf::Vector2u ws);
    MenuState getState() const;

    void render(sf::RenderTarget* target);

private:
    std::vector<sf::Text> menuOptions;
    sf::Font font;
    int currentIndex;
    MenuState currentState;

    void loadMenuOptions(const std::vector<std::string>& options, int cs, sf::Vector2u ws);
    void loadMainMenu(int cs, sf::Vector2u ws);
    void loadSettingsMenu(int cs, sf::Vector2u ws);
    void loadSoundMenu(int cs, sf::Vector2u ws);
    void loadDisplayMenu(int cs, sf::Vector2u ws);
    void loadResolutionMenu(int cs, sf::Vector2u ws);
};
