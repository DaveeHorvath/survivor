#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <deque>
#include <array>
#include <vector>
#include "Constants.h"
#include <SFML/Graphics/Text.hpp>

class Player;
class Game;
class GameInput;
class Vampire;
class Wave;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
        WAITING,
        ACTIVE,
    };
    
    Game();
    ~Game();
    
    bool initialise();
    void update(float deltaTime);
    void resetLevel();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    void startGame();
    State getState() const { return m_state; }
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

    Player* getPlayer() const;
    sf::Texture* getPlayerTexture() { return &m_playerTexture; }
    sf::Texture* getVampireTexture() { return &m_vampTexture; }

    void vampireSpawner(float deltaTime);

    std::array<std::unique_ptr<Wave>, MaxWaveCount> p_waves;

    float p_enemySpeed = VampireSpeed;
    int p_scorePreKill = 1;

    float p_playerSpeed = PlayerSpeed;
    bool p_godMode = false;
    sf::Keyboard::Key p_playerup = sf::Keyboard::Up;
    sf::Keyboard::Key p_playerdown = sf::Keyboard::Down;
    sf::Keyboard::Key p_playerleft = sf::Keyboard::Left;
    sf::Keyboard::Key p_playerright = sf::Keyboard::Right;
    sf::Keyboard::Key p_playerattack = sf::Keyboard::Space;
private:
    std::unique_ptr<Player> m_pPlayer;

    State m_state;
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;

    float m_vampireCooldown = 0.0f;
    float m_nextVampireCooldown = 2.0f;
    int m_spawnCount = 0;
    int m_score = 0;
    
    sf::Font m_font;
    sf::Texture m_vampTexture;
    sf::Texture m_playerTexture;

    int m_currentWave = 0;
    void progressNormalMode(float deltaTime);
    void progressInfiniteMode(float deltaTime);
    void SpawnEnemy(const sf::Vector2f spawnPoint);
    std::vector<std::shared_ptr<Vampire>> m_aliveEnemies;
    std::deque<std::shared_ptr<Vampire>> m_deadEnemies;
};
