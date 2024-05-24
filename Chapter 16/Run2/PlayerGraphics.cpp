#include "PlayerGraphics.h"
#include "PlayerUpdate.h"

void PlayerGraphics::assemble(
    VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    m_PlayerUpdate =
        static_pointer_cast<PlayerUpdate>(genericUpdate);
    m_Position =
        m_PlayerUpdate->getPositionPointer();

    m_VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    canvas[m_VertexStartIndex].texCoords.x =
        texCoords.left;
    canvas[m_VertexStartIndex].texCoords.y =
        texCoords.top;
    canvas[m_VertexStartIndex + 1].texCoords.x =
        texCoords.left + texCoords.width;
    canvas[m_VertexStartIndex + 1].texCoords.y =
        texCoords.top;
    canvas[m_VertexStartIndex + 2].texCoords.x =
        texCoords.left + texCoords.width;
    canvas[m_VertexStartIndex + 2].texCoords.y =
        texCoords.top + texCoords.height;
    canvas[m_VertexStartIndex + 3].texCoords.x =
        texCoords.left;
    canvas[m_VertexStartIndex + 3].texCoords.y =
        texCoords.top + texCoords.height;
}

void PlayerGraphics::draw(VertexArray& canvas)
{
    const Vector2f& position =
        m_Position->getPosition();
    const Vector2f& scale =
        m_Position->getSize();

    canvas[m_VertexStartIndex].position =
        position;
    canvas[m_VertexStartIndex + 1].position =
        position + Vector2f(scale.x, 0);
    canvas[m_VertexStartIndex + 2].position =
        position + scale;
    canvas[m_VertexStartIndex + 3].position =
        position + Vector2f(0, scale.y);
}
