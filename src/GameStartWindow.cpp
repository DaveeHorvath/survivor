#include "GameStartWindow.h"
#include "imgui.h"
#include "Game.h"
#include <iostream>

GameStartWindow::GameStartWindow(Game* game) : m_game(game)
{
    memset(m_name, 0, 14);
}

void GameStartWindow::draw()
{
    ImGui::Begin("##", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowPos(ImVec2(1430,10));
    ImGui::SetWindowSize(ImVec2(160, 74));
    if (ImGui::Button("Start"))
    {
        std::string tmp(m_name);

        m_game->setName(tmp);
        m_game->startGame();
    }
    ImGui::InputTextWithHint("Name", "your name here", m_name, 13);
    ImGui::End();
}