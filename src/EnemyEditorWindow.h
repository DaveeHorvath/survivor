#pragma once

class Wave;
class Game;

class EnemyEditorWindow {
public:
    EnemyEditorWindow(Game* game);
    void draw();
private:
    Game* m_game;
};