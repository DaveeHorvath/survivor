#include "GameStartWindow.h"
#include "imgui.h"
#include "Game.h"

GameStartWindow::GameStartWindow(Game* game) : m_game(game)
{
}

void GameStartWindow::draw()
{
    ImGui::Begin("##");
    if (ImGui::Button("start"))
        m_game->startGame();
    ImGui::End();
}