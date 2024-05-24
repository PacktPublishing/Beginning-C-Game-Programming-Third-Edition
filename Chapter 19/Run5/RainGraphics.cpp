#include "RainGraphics.h"
#include "RainGraphics.h"
#include "Animator.h"

RainGraphics::RainGraphics(
    FloatRect* playerPosition,
    float horizontalOffset,
    float verticalOffset,
    int rainCoveragePerObject)
{
    m_PlayerPosition = playerPosition;
    m_HorizontalOffset = horizontalOffset;
    m_VerticalOffset = verticalOffset;

    m_Scale.x = rainCoveragePerObject;
    m_Scale.y = rainCoveragePerObject;
}

void RainGraphics::assemble(VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    m_Animator = new Animator(
        texCoords.left,
        texCoords.top,
        4,// Frames
        texCoords.width * 4,
        texCoords.height,
        8);// FPS

    m_VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

}

void RainGraphics::draw(VertexArray& canvas)
{
    const Vector2f& position =
        m_PlayerPosition->getPosition()
        - Vector2f(m_Scale.x / 2 + m_HorizontalOffset,
            m_Scale.y / 2 + m_VerticalOffset);

    // Move the rain to keep up with the player
    canvas[m_VertexStartIndex].position = position;
    canvas[m_VertexStartIndex + 1].position =
        position + Vector2f(m_Scale.x, 0);
    canvas[m_VertexStartIndex + 2].position =
        position + m_Scale;
    canvas[m_VertexStartIndex + 3].position =
        position + Vector2f(0, m_Scale.y);

    //Cycle trough the frames
    m_SectionToDraw =
        m_Animator->getCurrentFrame(false);

    // Remember the section of the texture to draw
    const int uPos = m_SectionToDraw->left;
    const int vPos = m_SectionToDraw->top;
    const int texWidth = m_SectionToDraw->width;
    const int texHeight = m_SectionToDraw->height;

    canvas[m_VertexStartIndex].texCoords.x =
        uPos;
    canvas[m_VertexStartIndex].texCoords.y =
        vPos;
    canvas[m_VertexStartIndex + 1].texCoords.x =
        uPos + texWidth;
    canvas[m_VertexStartIndex + 1].texCoords.y =
        vPos;
    canvas[m_VertexStartIndex + 2].texCoords.x =
        uPos + texWidth;
    canvas[m_VertexStartIndex + 2].texCoords.y =
        vPos + texHeight;
    canvas[m_VertexStartIndex + 3].texCoords.x =
        uPos;
    canvas[m_VertexStartIndex + 3].texCoords.y =
        vPos + texHeight;

}
