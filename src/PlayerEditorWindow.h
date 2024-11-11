#pragma once

class Wave;
class Game;
#include <SFML/Window/Keyboard.hpp>
#include <string>

class PlayerEditorWindow {
public:
    PlayerEditorWindow(Game* game);
    void draw();
private:
    Game* m_game;
    void InputSelector(const std::string& buttonName, sf::Keyboard::Key& target);
};