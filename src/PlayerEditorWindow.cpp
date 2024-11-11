#include "PlayerEditorWindow.h"
#include "imgui.h"
#include "Game.h"

PlayerEditorWindow::PlayerEditorWindow(Game *game) : m_game(game)
{
}

void PlayerEditorWindow::draw()
{
    ImGui::Begin("Player Editor", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
    ImGui::SetWindowPos(ImVec2(10,730));
    ImGui::SetWindowSize(ImVec2(400, 200));

    ImGui::DragFloat("Player Speed", &(m_game->p_playerSpeed));
    ImGui::Checkbox("Godmode", &m_game->p_godMode);

    InputSelector("Up", m_game->p_playerup);
    InputSelector("Down", m_game->p_playerdown);
    InputSelector("Left", m_game->p_playerleft);
    InputSelector("Right", m_game->p_playerright);
    InputSelector("Attack", m_game->p_playerattack);

    ImGui::End();
}

void PlayerEditorWindow::InputSelector(const std::string& buttonName, sf::Keyboard::Key& target)
{
    std::string current = sf::Keyboard::getDescription(static_cast<sf::Keyboard::Scancode>(target));
    if (ImGui::BeginCombo(buttonName.c_str(), current.c_str()))
    {
        for (int key = sf::Keyboard::Key::Unknown; key != sf::Keyboard::Key::Num0 + 1; key++)
        {
            bool isSelected = target == key;
            std::string name = sf::Keyboard::getDescription(static_cast<sf::Keyboard::Scancode>(key));
            if (ImGui::Selectable(name.c_str(), &isSelected))
                target = static_cast<sf::Keyboard::Key>(key);
        }
        for (int key = sf::Keyboard::Key::Left; key != sf::Keyboard::Key::F1; key++)
        {
            bool isSelected = target == key;
            std::string name = sf::Keyboard::getDescription(static_cast<sf::Keyboard::Scancode>(key));
            if (ImGui::Selectable(name.c_str(), &isSelected))
                target = static_cast<sf::Keyboard::Key>(key);
        }
        ImGui::EndCombo();
    }
}