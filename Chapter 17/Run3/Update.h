#pragma once
#include "Component.h"
#include "SFML/Graphics.hpp"

class LevelUpdate;
class PlayerUpdate;

class Update :
    public Component
{
private:
public:
    Update();
    virtual void assemble(
        shared_ptr<LevelUpdate> levelUpdate,
        shared_ptr<PlayerUpdate> playerUpdate) = 0;

    virtual void update(float timeSinceLastUpdate) = 0;
};