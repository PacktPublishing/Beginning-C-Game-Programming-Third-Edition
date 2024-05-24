#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Update;

class Graphics :
    public Component
{
private:

public:
    Graphics();
    virtual void assemble(
        VertexArray& canvas,
        shared_ptr<Update> genericUpdate,
        IntRect texCoords) = 0;

    virtual void draw(VertexArray& canvas) = 0;

};
