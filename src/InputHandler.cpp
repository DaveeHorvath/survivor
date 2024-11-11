#include "InputHandler.h"
#include "Weapon.h"
#include "Player.h"
#include "Game.h"

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{

    
}

GameInput::~GameInput()
{
    
}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }

    if (m_inputData.m_space)
    {
        m_pPlayer->attack();
    }
}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == m_pGame->p_playerup)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == m_pGame->p_playerdown)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == m_pGame->p_playerleft)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == m_pGame->p_playerright)
    {
        m_inputData.m_movingRight = true;
    }
    else if (key == m_pGame->p_playerattack)
    {
        if (m_inputData.m_spaceReleased)
        {
            m_inputData.m_space = true;
        }
        m_inputData.m_spaceReleased = false;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == m_pGame->p_playerup)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == m_pGame->p_playerdown)
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == m_pGame->p_playerleft)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == m_pGame->p_playerright)
    {
        m_inputData.m_movingRight = false;
    }
    else if (key == m_pGame->p_playerattack)
    {
        m_inputData.m_space = false;
        m_inputData.m_spaceReleased = true;
    }
}
