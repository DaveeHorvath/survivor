#include "Vampire.h"
#include "Constants.h"
#include "Game.h"
#include "Weapon.h"
#include "Player.h"
#include "MathUtils.h"

Vampire::Vampire(Game* game, sf::Vector2f position) :
    Rectangle(sf::Vector2f(VampireWidth, VampireHeight)),
    m_pGame(game)
{
    setPosition(position);
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setIsKilled(false);

    m_sprite.setTexture(*m_pGame->getVampireTexture());
    m_sprite.setScale(2.0f, 2.0f);
}

void Vampire::update(float deltaTime)
{    
    Player* pPlayer = m_pGame->getPlayer();

    // only kill when weapon is drawn
    if (collidesWith(pPlayer->getWeapon()) && pPlayer->getWeapon()->isActive())
    {
        setIsKilled(true);
        return;
    }

    if (collidesWith(pPlayer))
    {
        if (pPlayer->isDead() == false)
            m_pGame->saveScore();
        pPlayer->setIsDead(true);
    }

    sf::Vector2f playerCenter = pPlayer->getCenter();
    sf::Vector2f direction = VecNormalized(playerCenter - getCenter());
    // passing as rvalue could have minimal speedup on a bigger scale
    sf::Transformable::move(direction * m_pGame->p_enemySpeed * deltaTime);
    m_sprite.setPosition(getPosition());
}