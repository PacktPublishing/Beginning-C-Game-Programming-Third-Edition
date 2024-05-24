#include "MenuUpdate.h"
#include "LevelUpdate.h"
#include "PlayerUpdate.h"
#include "SoundEngine.h"

MenuUpdate::MenuUpdate(RenderWindow* window)
{
    m_Window = window;

}


FloatRect* MenuUpdate::getPositionPointer()
{
    return &m_Position;
}

bool* MenuUpdate::getGameOverPointer()
{
    return &m_GameOver;
}

InputReceiver* MenuUpdate::getInputReceiver()
{
    return &m_InputReceiver;
}

void MenuUpdate::assemble(
    shared_ptr<LevelUpdate> levelUpdate,
    shared_ptr<PlayerUpdate> playerUpdate)
{

    m_PlayerPosition =
        playerUpdate->getPositionPointer();
    m_IsPaused =
        levelUpdate->getIsPausedPointer();

    m_Position.height = 75;
    m_Position.width = 75;

    SoundEngine::startMusic();
    SoundEngine::pauseMusic();
}

void MenuUpdate::handleInput()
{
    for (const Event& event :
        m_InputReceiver.getEvents())
    {
        if (event.type ==
            Event::KeyPressed)
        {
            if (event.key.code ==
                Keyboard::F1 && m_IsVisible)
            {
                if (SoundEngine::mMusicIsPlaying)
                {
                    SoundEngine::stopMusic();
                }
                m_Window->close();
            }
        }

        if (event.type == Event::KeyReleased)
        {
            if (event.key.code ==
                Keyboard::Escape)
            {
                m_IsVisible = !m_IsVisible;

                *m_IsPaused = !*m_IsPaused;

                if (m_GameOver)
                {
                    m_GameOver = false;
                }

                if (!*m_IsPaused)
                {
                    SoundEngine::resumeMusic();
                    SoundEngine::playClick();
                }

                if (*m_IsPaused)
                {
                    SoundEngine::pauseMusic();
                    SoundEngine::playClick();
                }

            }
        }
    }

    m_InputReceiver.clearEvents();

}

void MenuUpdate::update(float fps)
{
    handleInput();

    if (*m_IsPaused && !m_IsVisible)// Game over :-(
    {
        m_IsVisible = true;
        m_GameOver = true;
    }

    if (m_IsVisible)
    {
        // Follow the player
        m_Position.left =
            m_PlayerPosition->getPosition().x -
            m_Position.width / 2;
        m_Position.top =
            m_PlayerPosition->getPosition().y -
            m_Position.height / 2;
    }
    else
    {

        m_Position.left = -999;
        m_Position.top = -999;
    }

}

