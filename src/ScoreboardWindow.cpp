#include "ScoreboardWindow.h"
#include "imgui.h"
#include "Game.h"
#include <iostream>

ScoreboardWindow::ScoreboardWindow(Game *game) : m_game(game)
{
}

void ScoreboardWindow::draw()
{
    ImGui::Begin("Scoreboard", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowPos(ImVec2(1430, 94));
    ImGui::SetWindowSize(ImVec2(160, 100));

    for (auto& score : m_game->getScores())
    {
        ImGui::TextColored({1,0,0,1}, "%s %i", score.first.c_str(), score.second);
    }


    ImGui::End();
}
