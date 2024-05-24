#include "MenuGraphics.h"
#include "MenuUpdate.h"

void MenuGraphics::assemble(
    VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    m_MenuPosition = static_pointer_cast<MenuUpdate>(
        genericUpdate)->getPositionPointer();
    m_GameOver = static_pointer_cast<MenuUpdate>(
        genericUpdate)->getGameOverPointer();
    m_CurrentStatus = *m_GameOver;

    m_VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    // Remember the UV coordinates 
    // because we manipulate them later
    uPos = texCoords.left;
    vPos = texCoords.top;
    texWidth = texCoords.width;
    texHeight = texCoords.height;

    canvas[m_VertexStartIndex].texCoords.x = uPos;
    canvas[m_VertexStartIndex].texCoords.y =
        vPos + texHeight;
    canvas[m_VertexStartIndex + 1].texCoords.x =
        uPos + texWidth;
    canvas[m_VertexStartIndex + 1].texCoords.y =
        vPos + texHeight;
    canvas[m_VertexStartIndex + 2].texCoords.x =
        uPos + texWidth;
    canvas[m_VertexStartIndex + 2].texCoords.y =
        vPos + texHeight + texHeight;
    canvas[m_VertexStartIndex + 3].texCoords.x =
        uPos;
    canvas[m_VertexStartIndex + 3].texCoords.y =
        vPos + texHeight + texHeight;
}

void MenuGraphics::draw(VertexArray& canvas)
{

    if (*m_GameOver && !m_CurrentStatus)
        // current status has just switched to game over
    {
        // Each v coordinate is doubled to 
        // reference the texture below
        m_CurrentStatus = *m_GameOver;
        canvas[m_VertexStartIndex].texCoords.x =
            uPos;
        canvas[m_VertexStartIndex].texCoords.y =
            vPos + texHeight;
        canvas[m_VertexStartIndex + 1].texCoords.x =
            uPos + texWidth;
        canvas[m_VertexStartIndex + 1].texCoords.y =
            vPos + texHeight;
        canvas[m_VertexStartIndex + 2].texCoords.x =
            uPos + texWidth;
        canvas[m_VertexStartIndex + 2].texCoords.y =
            vPos + texHeight + texHeight;
        canvas[m_VertexStartIndex + 3].texCoords.x =
            uPos;
        canvas[m_VertexStartIndex + 3].texCoords.y =
            vPos + texHeight + texHeight;
    }
    else if (!*m_GameOver && m_CurrentStatus)
    {
        m_CurrentStatus = *m_GameOver;
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

    const Vector2f& position =
        m_MenuPosition->getPosition();

    canvas[m_VertexStartIndex].position =
        position;
    canvas[m_VertexStartIndex + 1].position =
        position + Vector2f(m_MenuPosition->getSize().x, 0);
    canvas[m_VertexStartIndex + 2].position =
        position + m_MenuPosition->getSize();
    canvas[m_VertexStartIndex + 3].position =
        position + Vector2f(0, m_MenuPosition->getSize().y);
}
