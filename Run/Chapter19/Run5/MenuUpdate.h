#pragma once
#include "Update.h"
#include "InputReceiver.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class MenuUpdate :
    public Update
{
private:
    FloatRect m_Position;
    InputReceiver m_InputReceiver;
    FloatRect* m_PlayerPosition = nullptr;
    bool m_IsVisible = false;
    bool* m_IsPaused;
    bool m_GameOver;
    RenderWindow* m_Window;

public:
    MenuUpdate(RenderWindow* window);
    void handleInput();
    FloatRect* getPositionPointer();
    bool* getGameOverPointer();
    InputReceiver* getInputReceiver();


    //From Update : Component
    void update(float fps) override;
    void assemble(
        shared_ptr<LevelUpdate> levelUpdate,
        shared_ptr<PlayerUpdate> playerUpdate)
        override;
};
