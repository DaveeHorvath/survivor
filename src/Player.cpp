#include "Player.h"
#include "Weapon.h"
#include "InputHandler.h"
#include "Constants.h"
#include <vector>
#include "Game.h"
#include "MathUtils.h"

Player::Player(Game* pGame) :
    Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight)),
    m_pGame(pGame),
    m_pWeapon(std::make_unique<Weapon>())
{
    setOrigin(sf::Vector2f(0.0f, 0.0f));
}

bool Player::initialise()
{
    m_sprite.setTexture(*m_pGame->getPlayerTexture());
    m_sprite.setScale(3.5f, 3.5f);
    setIsDead(false);
    setPosition(ScreenWidth / 2, ScreenHeight / 2);
    m_sprite.setPosition(getPosition());
    // this didnt reset the weapons position on restart, which sometimes left the weapon floating on the startscreen
    m_pWeapon->setActive(false);
    return true;
}

void Player::move(InputData inputData, float deltaTime)
{
    // this was missing the normalised movement, moving faster when pressing both
    // refactored to be inline with other code in codebase
    sf::Vector2f playerDirection;
    
    playerDirection.x -= inputData.m_movingLeft;
    playerDirection.x += inputData.m_movingRight;
    playerDirection.y -= inputData.m_movingUp;
    playerDirection.y += inputData.m_movingDown;
    playerDirection = VecNormalized(playerDirection);

    sf::Transformable::move(playerDirection * PlayerSpeed * deltaTime);
    // this was missing the y direction clamp and the sprite size offset
    setPosition(
        std::clamp(
            getPosition().x, 0.0f, (float)ScreenWidth - m_sprite.getTextureRect().width * m_sprite.getScale().x
        ),
        std::clamp(
            getPosition().y, 0.0f, (float)ScreenHeight - m_sprite.getTextureRect().height * m_sprite.getScale().y
        )
    );

    if (m_pWeapon->isActive() == false)
    {
        if (inputData.m_movingLeft == true && inputData.m_movingRight == false)
            m_direction = LEFT;
        else if (inputData.m_movingLeft == false && inputData.m_movingRight == true)
            m_direction = RIGHT;
    }
}

void Player::attack()
{
    m_pWeapon->setActive(true);
}

void Player::update(float deltaTime)
{
    sf::Vector2f weaponSize = m_pWeapon->getSize();

    m_sprite.setPosition(getPosition());
    m_pWeapon->setPosition(sf::Vector2f(
        getCenter().x - (m_direction == LEFT ? weaponSize.x : 0.0f),
        getCenter().y - weaponSize.y / 2.0f));
    m_pWeapon->update(deltaTime);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Rectangle::draw(target, states);
    m_pWeapon->draw(target, states);
}