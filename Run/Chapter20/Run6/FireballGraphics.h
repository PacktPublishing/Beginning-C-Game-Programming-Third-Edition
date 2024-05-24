#pragma once
#include "Graphics.h"

class Animator;
class PlayerUpdate;

class FireballGraphics :
    public Graphics
{
private:
    FloatRect* m_Position;
    int m_VertexStartIndex;

    bool* m_FacingRight = nullptr;

    Animator* m_Animator;
    IntRect* m_SectionToDraw;

    std::shared_ptr<PlayerUpdate> m_PlayerUpdate;

public:

    // From Graphics : Component
    void draw(VertexArray& canvas) override;
    void assemble(VertexArray& canvas,
        shared_ptr<Update> genericUpdate,
        IntRect texCoords) override;
};
