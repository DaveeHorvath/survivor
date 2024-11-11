#pragma once

class Game;

class ScoreboardWindow {
public:
    ScoreboardWindow(Game* game);
    void draw();
private:
    Game* m_game;
};