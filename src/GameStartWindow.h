#pragma once

class Game;

class GameStartWindow {
public:
    GameStartWindow(Game* game);
    void draw();
private:
    Game* m_game;
};