#include "PlayerGraphics.h"
#include "PlayerUpdate.h"
#include "Animator.h"

void PlayerGraphics::assemble(VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{

    m_PlayerUpdate = static_pointer_cast<PlayerUpdate>(genericUpdate);
    m_Position = m_PlayerUpdate->getPositionPointer();

    m_Animator = new Animator(
        texCoords.left,
        texCoords.top,
        6,// 6 frames
        texCoords.width * 6,
        texCoords.height,
        12);// FPS

    // Get the first frame of animation
    m_SectionToDraw = m_Animator->getCurrentFrame(false);
    m_StandingStillSectionToDraw = m_Animator->getCurrentFrame(false);

    m_VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);
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


    if (m_PlayerUpdate->m_RightIsHeldDown &&
        !m_PlayerUpdate->m_InJump &&
        !m_PlayerUpdate->m_BoostIsHeldDown &&
        m_PlayerUpdate->m_IsGrounded)
    {
        m_SectionToDraw = m_Animator->getCurrentFrame(false);
    }

    if (m_PlayerUpdate->m_LeftIsHeldDown &&
        !m_PlayerUpdate->m_InJump &&
        !m_PlayerUpdate->m_BoostIsHeldDown &&
        m_PlayerUpdate->m_IsGrounded)
    {
        m_SectionToDraw = m_Animator->getCurrentFrame(true);// reversed
    }
    else
    {
        // Test the players facing position
        // in case it changed while jumping or boosting
        // This value is used in the final animation option
        if (m_PlayerUpdate->m_LeftIsHeldDown)
        {
            m_LastFacingRight = false;
        }
        else
        {
            m_LastFacingRight = true;
        }
    }

    const int uPos = m_SectionToDraw->left;
    const int vPos = m_SectionToDraw->top;
    const int texWidth = m_SectionToDraw->width;
    const int texHeight = m_SectionToDraw->height;

    if (m_PlayerUpdate->m_RightIsHeldDown &&
        !m_PlayerUpdate->m_InJump &&
        !m_PlayerUpdate->m_BoostIsHeldDown)
    {
        canvas[m_VertexStartIndex].texCoords.x
            = uPos;
        canvas[m_VertexStartIndex].texCoords.y
            = vPos;
        canvas[m_VertexStartIndex + 1].texCoords.x
            = uPos + texWidth;
        canvas[m_VertexStartIndex + 1].texCoords.y
            = vPos;
        canvas[m_VertexStartIndex + 2].texCoords.x
            = uPos + texWidth;
        canvas[m_VertexStartIndex + 2].texCoords.y
            = vPos + texHeight;
        canvas[m_VertexStartIndex + 3].texCoords.x
            = uPos;
        canvas[m_VertexStartIndex + 3].texCoords.y
            = vPos + texHeight;
    }

    else if (m_PlayerUpdate->m_LeftIsHeldDown &&
        !m_PlayerUpdate->m_InJump &&
        !m_PlayerUpdate->m_BoostIsHeldDown)
    {
        canvas[m_VertexStartIndex].texCoords.x
            = uPos;
        canvas[m_VertexStartIndex].texCoords.y
            = vPos;
        canvas[m_VertexStartIndex + 1].texCoords.x
            = uPos - texWidth;
        canvas[m_VertexStartIndex + 1].texCoords.y
            = vPos;
        canvas[m_VertexStartIndex + 2].texCoords.x
            = uPos - texWidth;
        canvas[m_VertexStartIndex + 2].texCoords.y
            = vPos + texHeight;
        canvas[m_VertexStartIndex + 3].texCoords.x
            = uPos;
        canvas[m_VertexStartIndex + 3].texCoords.y
            = vPos + texHeight;
    }


    else if (m_PlayerUpdate->m_RightIsHeldDown &&
        m_PlayerUpdate->m_BoostIsHeldDown)
    {
        canvas[m_VertexStartIndex].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[m_VertexStartIndex].texCoords.y =
            BOOST_TEX_TOP;
        canvas[m_VertexStartIndex + 1].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_VertexStartIndex + 1].texCoords.y =
            BOOST_TEX_TOP;
        canvas[m_VertexStartIndex + 2].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_VertexStartIndex + 2].texCoords.y =
            BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
        canvas[m_VertexStartIndex + 3].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[m_VertexStartIndex + 3].texCoords.y =
            BOOST_TEX_TOP + BOOST_TEX_HEIGHT;
    }
    else if (m_PlayerUpdate->m_LeftIsHeldDown &&
        m_PlayerUpdate->m_BoostIsHeldDown)
    {
        canvas[m_VertexStartIndex].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_VertexStartIndex].texCoords.y = 0;
        canvas[m_VertexStartIndex + 1].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[m_VertexStartIndex + 1].texCoords.y = 0;
        canvas[m_VertexStartIndex + 2].texCoords.x =
            BOOST_TEX_LEFT;
        canvas[m_VertexStartIndex + 2].texCoords.y = 100;
        canvas[m_VertexStartIndex + 3].texCoords.x =
            BOOST_TEX_LEFT + BOOST_TEX_WIDTH;
        canvas[m_VertexStartIndex + 3].texCoords.y = 100;
    }

    else if (m_PlayerUpdate->m_BoostIsHeldDown)
    {
        canvas[m_VertexStartIndex].texCoords.x = 536;
        canvas[m_VertexStartIndex].texCoords.y = 0;
        canvas[m_VertexStartIndex + 1].texCoords.x = 605;
        canvas[m_VertexStartIndex + 1].texCoords.y = 0;
        canvas[m_VertexStartIndex + 2].texCoords.x = 605;
        canvas[m_VertexStartIndex + 2].texCoords.y = 100;
        canvas[m_VertexStartIndex + 3].texCoords.x = 536;
        canvas[m_VertexStartIndex + 3].texCoords.y = 100;
    }
    else
    {
        if (m_LastFacingRight)
        {
            canvas[m_VertexStartIndex].texCoords.x =
                m_StandingStillSectionToDraw->left;
            canvas[m_VertexStartIndex].texCoords.y =
                m_StandingStillSectionToDraw->top;
            canvas[m_VertexStartIndex + 1].texCoords.x =
                m_StandingStillSectionToDraw->left + texWidth;
            canvas[m_VertexStartIndex + 1].texCoords.y =
                m_StandingStillSectionToDraw->top;
            canvas[m_VertexStartIndex + 2].texCoords.x =
                m_StandingStillSectionToDraw->left + texWidth;
            canvas[m_VertexStartIndex + 2].texCoords.y =
                m_StandingStillSectionToDraw->top + texHeight;
            canvas[m_VertexStartIndex + 3].texCoords.x =
                m_StandingStillSectionToDraw->left;
            canvas[m_VertexStartIndex + 3].texCoords.y =
                m_StandingStillSectionToDraw->top + texHeight;
        }
        else
        {
            canvas[m_VertexStartIndex].texCoords.x =
                m_StandingStillSectionToDraw->left + texWidth;
            canvas[m_VertexStartIndex].texCoords.y =
                m_StandingStillSectionToDraw->top;
            canvas[m_VertexStartIndex + 1].texCoords.x =
                m_StandingStillSectionToDraw->left;
            canvas[m_VertexStartIndex + 1].texCoords.y =
                m_StandingStillSectionToDraw->top;
            canvas[m_VertexStartIndex + 2].texCoords.x =
                m_StandingStillSectionToDraw->left;
            canvas[m_VertexStartIndex + 2].texCoords.y =
                m_StandingStillSectionToDraw->top + texHeight;
            canvas[m_VertexStartIndex + 3].texCoords.x =
                m_StandingStillSectionToDraw->left + texWidth;
            canvas[m_VertexStartIndex + 3].texCoords.y =
                m_StandingStillSectionToDraw->top + texHeight;
        }
    }
}

