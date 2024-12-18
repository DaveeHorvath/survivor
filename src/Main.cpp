#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Game.h"
#include <memory>
#include <iostream>

#include "ResourceManager.h"
#include "imgui-SFML.h"
#include "WaveEditorWindow.h"
#include "GameStartWindow.h"
#include "EnemyEditorWindow.h"
#include "PlayerEditorWindow.h"
#include "ScoreboardWindow.h"

int main(int argc, char* argv[])
{
    // ResourceManager Must be Instantiated here -- DO NOT CHANGE
    ResourceManager::init(argv[0]);

    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Survive");
    window.setKeyRepeatEnabled(false);
    srand(time(NULL));
    std::unique_ptr<Game> pGame = std::make_unique<Game>();
    if (!pGame->initialise())
    {
        std::cerr << "Game Failed to initialise" << std::endl;
        return 1;
    }

    // imgui windows for prototyping
    std::unique_ptr<WaveEditorWindow> waveEditor = std::make_unique<WaveEditorWindow>(pGame.get());
    std::unique_ptr<GameStartWindow> gameStartWindow = std::make_unique<GameStartWindow>(pGame.get());
    std::unique_ptr<EnemyEditorWindow> enemyEditorWindow = std::make_unique<EnemyEditorWindow>(pGame.get());
    std::unique_ptr<PlayerEditorWindow> playerEditorWindow = std::make_unique<PlayerEditorWindow>(pGame.get());
    std::unique_ptr<ScoreboardWindow> scoreboardWindow = std::make_unique<ScoreboardWindow>(pGame.get());

    // init imgui
    ImGui::SFML::Init(window);
    
    sf::Clock clock;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            switch(event.type)
            {
                case sf::Event::Closed:
                    // "close requested" event: we close the window
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    pGame->onKeyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    pGame->onKeyReleased(event.key.code);
                    break;
                default:
                    break;
            }
        }
        
        sf::Time elapsedTime = clock.getElapsedTime();
        ImGui::SFML::Update(window, clock.restart());
        pGame->update(elapsedTime.asSeconds());
        // draw the debug windows if the game isnt running
        if (pGame->getState() == Game::State::WAITING)
        {
            waveEditor->draw();
            gameStartWindow->draw();
            enemyEditorWindow->draw();
            playerEditorWindow->draw();
            scoreboardWindow->draw();
        }
        
        // clear the window with black color
        window.clear(sf::Color::Black);
        
        window.draw(*pGame.get());
        ImGui::SFML::Render(window);
        
        // end the current frame
        window.display();
    }

    ImGui::SFML::Shutdown();
    
    return 0;
}
