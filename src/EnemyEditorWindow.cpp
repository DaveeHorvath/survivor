#include "EnemyEditorWindow.h"
#include "imgui.h"
#include "Game.h"
EnemyEditorWindow::EnemyEditorWindow(Game *game) : m_game(game)
{
}

void EnemyEditorWindow::draw()
{
    ImGui::Begin("EnemyEditor", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
    ImGui::SetWindowPos(ImVec2(10,650));
    ImGui::SetWindowSize(ImVec2(400, 80));

    ImGui::DragFloat("Enemy Speed", &(m_game->p_enemySpeed), 1, 0, 300);
    ImGui::DragInt("Score Per Kill", &(m_game->p_scorePreKill), 1, 0, 10);

    ImGui::End();
}
