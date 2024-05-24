#pragma once
#include "Update.h"
#include "InputReceiver.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class CameraUpdate :
    public Update
{

private:
    FloatRect m_Position;
    FloatRect* m_PlayerPosition;

    bool m_ReceivesInput = false;
    InputReceiver* m_InputReceiver = nullptr;

public:
    FloatRect* getPositionPointer();

    void handleInput();
    InputReceiver* getInputReceiver();

    //From Update : Component
    void assemble(shared_ptr<LevelUpdate> levelUpdate,
        shared_ptr<PlayerUpdate> playerUpdate) override;

    void update(float fps) override;

};
