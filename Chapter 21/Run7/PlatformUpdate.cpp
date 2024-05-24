#include "PlatformUpdate.h"
#include "PlayerUpdate.h"

FloatRect* PlatformUpdate::getPositionPointer()
{
    return &m_Position;
}

void PlatformUpdate::assemble(
    shared_ptr<LevelUpdate> levelUpdate,
    shared_ptr<PlayerUpdate> playerUpdate)
{
    //mPosition = position;
    m_PlayerPosition = playerUpdate->getPositionPointer();
    m_PlayerIsGrounded = playerUpdate->getGroundedPointer();
}

void PlatformUpdate::update(float fps)
{

    if (m_Position.intersects(*m_PlayerPosition))
    {
        Vector2f playerFeet(m_PlayerPosition->left +
            m_PlayerPosition->width / 2,
            m_PlayerPosition->top +
            m_PlayerPosition->height);

        Vector2f playerRight(m_PlayerPosition->left +
            m_PlayerPosition->width,
            m_PlayerPosition->top +
            m_PlayerPosition->height / 2);

        Vector2f playerLeft(m_PlayerPosition->left,
            m_PlayerPosition->top +
            m_PlayerPosition->height / 2);

        Vector2f playerHead(m_PlayerPosition->left +
            m_PlayerPosition->width / 2,
            m_PlayerPosition->top);

        if (m_Position.contains(playerFeet))
        {
            if (playerFeet.y > m_Position.top)
            {
                m_PlayerPosition->top =
                    m_Position.top -
                    m_PlayerPosition->height;

                *m_PlayerIsGrounded = true;
            }
        }

        else if (m_Position.contains(playerRight))
        {
            m_PlayerPosition->left =
                m_Position.left - m_PlayerPosition->width;
        }

        else if (m_Position.contains(playerLeft))
        {
            m_PlayerPosition->left =
                m_Position.left + m_Position.width;
        }

        else if (m_Position.contains(playerHead))
        {
            m_PlayerPosition->top =
                m_Position.top + m_Position.height;
        }
    }
}
