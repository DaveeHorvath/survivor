#include "Wave.h"
#include <iostream>
#include <algorithm>

Wave::Wave(const std::string& name)
: m_name(name), m_gen(m_random()), m_waveDuration(10), p_enemyNumber(10)
{
    std::for_each(m_directions.begin(), m_directions.end(), [](int& x){x = rand() % 80;});
}

void Wave::init()
{
    // only create the distribution once we enter the gamestate, if all are 0 set first to 1
    if (std::all_of(m_directions.begin(), m_directions.end(), [](int x){return x == 0;}))
        m_directions[0] = 1;
    m_distribution.param({c_directionRadians.begin(), c_directionRadians.end(), m_directions.begin()});
    m_coolDown = m_waveDuration / p_enemyNumber;
    p_enemyRemaining = p_enemyNumber;
}

float Wave::getSpawnCooldown(const float &deltaTime)
{
    if (p_enemyNumber == 0)
        return 1; // return 1 so no spawn happens

    m_coolDown -= deltaTime;
    if (m_coolDown <= 0.0f)
    {
        m_coolDown = m_waveDuration / p_enemyNumber;
        p_enemyRemaining--;
        return 0;
    }
    return m_coolDown;
}

Wave::~Wave()
{
}

sf::Vector2f Wave::getNextSpawnDirection()
{
    // allows me to decide which directions they should mostly come from, and since it returns it on a contioum,
    // all angles between the exact values will be considered uniformly
    double rad = m_distribution(m_gen);
    // simple unit circle location
    return {static_cast<float>(std::cos(rad)), -1.0f * static_cast<float>(std::sin(rad))};
}