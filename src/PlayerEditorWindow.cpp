#include "PlayerEditorWindow.h"
#include "imgui.h"
#include "Game.h"
#include <iostream>
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
    // use the fact that enums have their possible values in order so if we just cast them from int should be fine
    std::string current = sf::Keyboard::getDescription(sf::Keyboard::delocalize(static_cast<sf::Keyboard::Key>(target)));
    if (ImGui::BeginCombo(buttonName.c_str(), current.c_str()))
    {
        // a-z
        for (int key = sf::Keyboard::Key::Unknown; key != sf::Keyboard::Key::Num0 + 1; key++)
        {
            bool isSelected = target == key;
            std::string name = sf::Keyboard::getDescription(sf::Keyboard::delocalize(static_cast<sf::Keyboard::Key>(key)));
            if (ImGui::Selectable(name.c_str(), &isSelected))
                target = static_cast<sf::Keyboard::Key>(key);
        }
        // left -> numpad end
        for (int key = sf::Keyboard::Key::Left; key != sf::Keyboard::Key::F1; key++)
        {
            bool isSelected = target == key;
            std::string name = sf::Keyboard::getDescription(sf::Keyboard::delocalize(static_cast<sf::Keyboard::Key>(key)));
            if (ImGui::Selectable(name.c_str(), &isSelected))
                target = static_cast<sf::Keyboard::Key>(key);
        }
        ImGui::EndCombo();
    }
}