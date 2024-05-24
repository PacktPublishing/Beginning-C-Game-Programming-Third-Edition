#pragma once
#include "Graphics.h"

class Animator;


class RainGraphics :
    public Graphics
{
private:
    FloatRect* m_PlayerPosition;

    int m_VertexStartIndex;
    Vector2f m_Scale;

    float m_HorizontalOffset;
    float m_VerticalOffset;

    Animator* m_Animator;
    IntRect* m_SectionToDraw;

public:
    RainGraphics(FloatRect* playerPosition,
        float horizontalOffset,
        float verticalOffset,
        int rainCoveragePerObject);

    // From Graphics : Component
    void draw(VertexArray& canvas) override;
    void assemble(VertexArray& canvas,
        shared_ptr<Update> genericUpdate,
        IntRect texCoords) override;
};

