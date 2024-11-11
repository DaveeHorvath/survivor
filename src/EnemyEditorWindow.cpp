#include "EnemyEditorWindow.h"
#include "imgui.h"
#include "Game.h"
EnemyEditorWindow::EnemyEditorWindow(Game *game) : m_game(game)
{
}

void EnemyEditorWindow::draw()
{
    ImGui::Begin("EnemyEditor", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
    ImGui::SetWindowPos(ImVec2(10,620));
    ImGui::SetWindowSize(ImVec2(400, 80));

    ImGui::DragFloat("Enemy Speed", &(m_game->p_enemySpeed));
    ImGui::DragInt("Score Per Kill", &(m_game->p_scorePreKill));

    ImGui::End();
}
