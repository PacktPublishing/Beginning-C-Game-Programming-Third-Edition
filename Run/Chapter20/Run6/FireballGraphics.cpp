#include "FireballGraphics.h"
#include "Animator.h"
#include "FireballUpdate.h"

void FireballGraphics::assemble(
    VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    shared_ptr<FireballUpdate> fu =
        static_pointer_cast
        <FireballUpdate>(genericUpdate);
    m_Position = fu->getPositionPointer();
    m_FacingRight = fu->getFacingRightPointer();

    m_Animator = new Animator(
        texCoords.left,
        texCoords.top,
        3,// 6 frames
        texCoords.width * 3,
        texCoords.height,
        6);// FPS

    // Get the first frame of animation
    m_SectionToDraw =
        m_Animator->getCurrentFrame(false);

    m_VertexStartIndex =
        canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
    const int uPos = texCoords.left;
    const int vPos = texCoords.top;
    const int texWidth = texCoords.width;
    const int texHeight = texCoords.height;

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

void FireballGraphics::draw(VertexArray& canvas)
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

    if (*m_FacingRight)
    {
        m_SectionToDraw =
            m_Animator->getCurrentFrame(false);
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
    else
    {
        // Doesn't make much difference to 
        // fire which order the frames are drawn
        // But front must be at front duh!!!!
        m_SectionToDraw = m_Animator->getCurrentFrame(true);// reversed
        const int uPos = m_SectionToDraw->left;
        const int vPos = m_SectionToDraw->top;
        const int texWidth = m_SectionToDraw->width;
        const int texHeight = m_SectionToDraw->height;

        canvas[m_VertexStartIndex].texCoords.x =
            uPos;
        canvas[m_VertexStartIndex].texCoords.y =
            vPos;
        canvas[m_VertexStartIndex + 1].texCoords.x =
            uPos - texWidth;
        canvas[m_VertexStartIndex + 1].texCoords.y =
            vPos;
        canvas[m_VertexStartIndex + 2].texCoords.x =
            uPos - texWidth;
        canvas[m_VertexStartIndex + 2].texCoords.y =
            vPos + texHeight;
        canvas[m_VertexStartIndex + 3].texCoords.x =
            uPos;
        canvas[m_VertexStartIndex + 3].texCoords.y =
            vPos + texHeight;
    }
}
