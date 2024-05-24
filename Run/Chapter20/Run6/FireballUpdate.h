#pragma once
#include "Update.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class FireballUpdate :
    public Update
{
private:
    FloatRect m_Position;

    FloatRect* m_PlayerPosition;
    bool* m_GameIsPaused = nullptr;
    float m_Speed = 250;
    float m_Range = 900;
    int m_MaxSpawnDistanceFromPlayer = 250;

    bool m_MovementPaused = true;
    Clock m_PauseClock;
    float m_PauseDurationTarget = 0;
    float m_MaxPause = 6;
    float m_MinPause = 1;
    //float mTimePaused = 0;
    bool m_LeftToRight = true;


public:
    FireballUpdate(bool* pausedPointer);
    bool* getFacingRightPointer();
    FloatRect* getPositionPointer();
    int getRandomNumber(int minHeight,
        int maxHeight);

    // From Update : Component

    void update(float fps) override;
    void assemble(shared_ptr<LevelUpdate> levelUpdate,
        shared_ptr<PlayerUpdate> playerUpdate)
        override;
};
