#pragma once

class Wave;
class Game;

class WaveEditorWindow {
public:
    WaveEditorWindow(Game* game);
    void draw();
private:
    Wave* m_currentWave;
    int m_selectedIndex;
    Game* m_game;
};