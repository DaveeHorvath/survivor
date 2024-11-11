#include "GameStartWindow.h"
#include "imgui.h"
#include "Game.h"

GameStartWindow::GameStartWindow(Game* game) : m_game(game)
{
}

void GameStartWindow::draw()
{
    ImGui::Begin("##", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowPos(ImVec2(1500,10));
    ImGui::SetWindowSize(ImVec2(60, 36));
    if (ImGui::Button("Start"))
        m_game->startGame();
    ImGui::End();
}