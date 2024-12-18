#include "WaveEditorWindow.h"
#include "imgui.h"
#include "Wave.h"
#include "Game.h"
#include <array>
#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <string>

WaveEditorWindow::WaveEditorWindow(Game* game) : m_game(game),  m_selectedIndex(0)
{
    if (m_game->p_waves.size() > 0)
        m_currentWave = m_game->p_waves[0].get();
}

void WaveEditorWindow::draw()
{
    ImGui::Begin("Wave Editor", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::SetWindowPos(ImVec2(10,10));
    ImGui::SetWindowSize(ImVec2(400, 640));
    if (ImGui::BeginCombo("Select Wave", m_currentWave->getName().c_str()))
    {
        for (int i = 0; i < m_game->p_waves.size(); i++)
        {
            bool isSelected = m_selectedIndex == i;
            if (ImGui::Selectable(m_game->p_waves[i]->getName().c_str(), &isSelected))
            {
                m_selectedIndex = i;
                m_currentWave = m_game->p_waves[i].get();
            }
        }
        ImGui::EndCombo();
    }
    if (ImGui::Button("Save Configuration"))
    {
        // sadly hardcoded, sorry
        std::ofstream file;
        file.open(ResourceManager::getFilePath("example.setup"), std::ios::trunc | std::ios::out);
        if (!file.good())
            std::cout << "Error while opening output file\n";
        for (auto& wave : m_game->p_waves)
        {
            file << wave->getName() << "\n";
            file << wave->p_enemyNumber << "\n";
            file << wave->m_waveDuration << "\n";
            for (auto& dist : wave->m_directions)
                file << dist << "\n";
        }
        file.close();
    }

    if (m_currentWave != nullptr)
    {
        // ImGui::Text("Number of enemies in Wave");
        ImGui::DragInt("EnemyNumber", &m_currentWave->p_enemyNumber, 1, 5, 50);
        ImGui::DragFloat("WaveDuration", &m_currentWave->m_waveDuration, 1, 5, 50);
        ImGui::Text("Directional Distribution");
        for (int i = 0; i < 8; i++)
            ImGui::SliderInt(std::to_string(i).c_str(), &m_currentWave->m_directions[i], 0, 100);

        // drawlist
        auto dl = ImGui::GetForegroundDrawList();
        // outline point calculated on paper
        std::array<ImVec2, 9> outline = {
                ImVec2(300, 80), ImVec2(220, 0), ImVec2(80, 0), ImVec2(0, 80), ImVec2(0, 220), ImVec2(80, 300), ImVec2(220, 300), ImVec2(300, 220),
                ImVec2(300, 80)
            };
        ImVec2 centerPoint(210, 490);
        // simple transformation to get the desired position
        for (auto& point : outline)
        {
            // move to the bottom
            point.x += 60;
            point.y += 340;
        }
        // draw the outline
        dl->AddPolyline(outline.data(), 9, 0x90ff1000, 0, 2);
        // get all the plotpoints that represent the distribution
        std::array<ImVec2, 8> plot{};
        // draws the "axis" and the point between
        for (int i = 0; i < 8; i++)
        {
            dl->AddLine(centerPoint, outline[i], 0x8800ff00, 2);
            ImVec2 midPoint;
            // linear interpolation where the current weight is a precentile
            midPoint.x = outline[i].x * (m_currentWave->m_directions[i] / 100.0f) + centerPoint.x * (1 - m_currentWave->m_directions[i] / 100.0f);
            midPoint.y = outline[i].y * (m_currentWave->m_directions[i] / 100.0f) + centerPoint.y * (1 - m_currentWave->m_directions[i] / 100.0f);
            plot[i] = midPoint;
            // descirptors
            dl->AddText(midPoint, 0xffffffff, std::to_string(i).c_str());
            dl->AddCircleFilled(midPoint, 3, 0xffff0000);
        }
        // add the shape describing the distribution
        dl->AddConvexPolyFilled(plot.data(), 8, 0x80808000);
        // should be the following but my cmake setup somehow doesnt allow for it 
        // it is supposed to live in the imgui_draw.cpp file, which should be included based on my understanding
        // dl->AddConcavePolyFilled(plot.data(), 8, 0x80808000);
    }

    ImGui::End();
}