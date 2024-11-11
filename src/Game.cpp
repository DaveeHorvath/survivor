#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Rectangle.h"
#include "Vampire.h"
#include "Wave.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>(this)),
    m_vampireCooldown(2.0f),
    m_nextVampireCooldown(2.0f)
{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
    // needs slight change
    for (int i = 0; i < MaxWaveCount; i++)
        p_waves[i] = std::make_unique<Wave>("Wave" + std::to_string(i));
    m_aliveEnemies.clear();
    m_deadEnemies.clear();
}

Game::~Game()
{
}

bool Game::initialise()
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */

    if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }
    if (!m_vampTexture.loadFromFile(ResourceManager::getFilePath("vampire.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }
    if (!m_playerTexture.loadFromFile(ResourceManager::getFilePath("player.png")))
    {
        std::cerr << "Unable to load texture" << std::endl;
        return false;
    }

    resetLevel();
    return true;
}

void Game::resetLevel()
{
    m_aliveEnemies.clear();
    // no need to clear the dead enemies, we can reuse them on the next run

    m_pPlayer->initialise();
    m_pClock->restart();
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->update(deltaTime);

            vampireSpawner(deltaTime);
            for (auto& temp : m_aliveEnemies)
            {
                temp->update(deltaTime);
            }

            if (m_pPlayer->isDead())
            {
                m_state = State::WAITING;
                resetLevel();
            }
        }
        break;
    }

    for (auto it = m_aliveEnemies.begin(); it != m_aliveEnemies.end();)
    {
        if ((*it)->isKilled())
        {
            if (m_deadEnemies.size() < MaxDeadEnemiesStored)
                m_deadEnemies.push_front(*it);
            it = m_aliveEnemies.erase(it);
        }
        else
            it++;
    }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // no need to recreate every frame, nor to call all the functions
    // a good compiler should recognise that this needs to be called once
    static sf::Text startText;
    static sf::Text timerText;
    static sf::Text WaveText;
    static bool textSetupDone = false;

    if (!textSetupDone)
    {
        textSetupDone = true;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setStyle(sf::Text::Bold);
        startText.setPosition(sf::Vector2f((ScreenWidth - startText.getLocalBounds().getSize().x) * 0.5, 20));
        timerText.setFont(m_font);
        timerText.setFillColor(sf::Color::White);
        timerText.setStyle(sf::Text::Bold);
        WaveText.setFont(m_font);
        WaveText.setFillColor(sf::Color::White);
        WaveText.setStyle(sf::Text::Bold);
    }
    //  Draw texts.
    switch (m_state)
    {
    case State::WAITING:
        target.draw(startText);
        break;
    case State::ACTIVE:
        timerText.setString(std::to_string((int)m_pClock->getElapsedTime().asSeconds()));
        timerText.setPosition(sf::Vector2f((ScreenWidth - timerText.getLocalBounds().getSize().x) * 0.5, 20));
        WaveText.setString("Wave " + std::to_string(m_currentWave));
        WaveText.setPosition(sf::Vector2f((ScreenWidth - WaveText.getLocalBounds().getSize().x) * 0.5, 0));
        target.draw(timerText);
        target.draw(WaveText);
        break;
    }

    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_aliveEnemies)
        temp->draw(target, states);
}

void Game::startGame()
{
    m_state = State::ACTIVE;
    for (auto& wave : p_waves)
    {
        wave->init();
    }
    m_pClock->restart();
}

void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

Player* Game::getPlayer() const 
{
    return m_pPlayer.get();
}

void Game::vampireSpawner(float deltaTime)
{
    if (m_currentWave < p_waves.size())
        progressNormalMode(deltaTime);
    else
        progressInfiniteMode(deltaTime);
}

void Game::progressNormalMode(float deltaTime)
{
    // check the waves timings
    if (p_waves[m_currentWave]->getSpawnCooldown(deltaTime) > 0.0f)
        return;
    // spawn new enemy
    sf::Vector2f enemyDir = p_waves[m_currentWave]->getNextSpawnDirection();

    SpawnEnemy(enemyDir * static_cast<float>(ScreenWidth) * 0.6f + sf::Vector2f(ScreenWidth / 2, ScreenHeight / 2));
    if (p_waves[m_currentWave]->p_enemyRemaining <= 0)
        m_currentWave++;
}


/*
    this is the a big focus, as its decent for an infinity mode
    originally:
        inefficient -> no reuse of dead vampires, reallocating every time instead
        no agency on the gamedesigners part -> fully random spawnlocation
        looping over dead enemies makes it a bit slower
    fixes:
        alive and dead enemy tracking
*/
void Game::progressInfiniteMode(float deltaTime)
{
    if (m_vampireCooldown > 0.0f)
    {
        m_vampireCooldown -= deltaTime;
        return;
    }

    float randomXPos = rand() % ScreenWidth;
    float randomYPos = rand() % ScreenHeight;

    float distToRight = (float) ScreenWidth - randomXPos;
    float distToBottom = (float) ScreenHeight - randomYPos;

    float xMinDist = randomXPos < distToRight ? -randomXPos : distToRight;
    float yMinDist = randomYPos < distToBottom ? -randomYPos : distToBottom;

    if (abs(xMinDist) < abs(yMinDist))
        randomXPos += xMinDist;
    else
        randomYPos += yMinDist;

    sf::Vector2f spawnPosition = sf::Vector2f(randomXPos, randomYPos);
    SpawnEnemy(spawnPosition);

    m_spawnCount++;
    if (m_spawnCount % 5 == 0)
    {
        // unsafe, negative times didnt make sense
        if (m_nextVampireCooldown > MinEnemySpawnTime)
            m_nextVampireCooldown -= 0.1f;
    }
    m_vampireCooldown = m_nextVampireCooldown;
}

void Game::SpawnEnemy(const sf::Vector2f spawnPoint)
{
    if (m_deadEnemies.size() == 0)
        m_aliveEnemies.push_back(std::make_shared<Vampire>(this, spawnPoint));
    else
    {
        m_deadEnemies.back()->setPosition(spawnPoint);
        m_deadEnemies.back()->setIsKilled(false);
        m_aliveEnemies.push_back(m_deadEnemies.back());
        m_deadEnemies.pop_back();
    }
}