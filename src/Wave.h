#pragma once

#include <array>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <random>
#include <math.h>

class Wave {
public:
    Wave(const std::string& name);
    ~Wave();
    std::array<int, 8> m_directions;
    std::string& getName() { return m_name; }
    int p_enemyNumber;
    int p_enemyRemaining;
    float m_waveDuration;
    sf::Vector2f getNextSpawnDirection();
    void init();
    float getSpawnCooldown(const float& deltaTime);
private:
    std::string m_name;
    float m_coolDown;

    // according to cppreference https://en.cppreference.com/w/cpp/numeric/random/piecewise_constant_distribution
    std::random_device m_random;
    std::mt19937 m_gen;
    const std::array<double, 9> c_directionRadians{
        0, M_PI / 4, M_PI / 2, 3 * M_PI / 4, M_PI, 5 * M_PI / 4, 3 * M_PI / 2, 7* M_PI / 4, 2 * M_PI
    };
    std::piecewise_constant_distribution<> m_distribution;
};