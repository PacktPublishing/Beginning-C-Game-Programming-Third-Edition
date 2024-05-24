#include "CameraGraphics.h"
#include "CameraUpdate.h"

CameraGraphics::CameraGraphics(
    RenderWindow* window, Texture* texture,
    Vector2f viewSize, FloatRect viewport)
{
    m_Window = window;
    m_Texture = texture;

    m_View.setSize(viewSize);
    m_View.setViewport(viewport);

    // The mini map viewport is less than 1
    if (viewport.width < 1)
    {
        m_IsMiniMap = true;
    }
    else
    {
        // Only the full screen camera has the time text
        m_Font.loadFromFile("fonts/KOMIKAP_.ttf");
        m_Text.setFont(m_Font);
        m_Text.setFillColor(Color(255, 0, 0, 255));
        m_Text.setScale(0.2f, 0.2f);
    }
}

void CameraGraphics::assemble(
    VertexArray& canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    shared_ptr<CameraUpdate> cameraUpdate =
        static_pointer_cast<CameraUpdate>(genericUpdate);
    m_Position = cameraUpdate->getPositionPointer();

    m_VertexStartIndex = canvas.getVertexCount();
    canvas.resize(canvas.getVertexCount() + 4);

    const int uPos = texCoords.left;
    const int vPos = texCoords.top;
    const int texWidth = texCoords.width;
    const int texHeight = texCoords.height;

    canvas[m_VertexStartIndex].texCoords.x = uPos;
    canvas[m_VertexStartIndex].texCoords.y = vPos;
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

float* CameraGraphics::getTimeConnection()
{
    return &m_Time;
}

void CameraGraphics::draw(VertexArray& canvas)
{
    m_View.setCenter(m_Position->getPosition());

    Vector2f startPosition;
    startPosition.x = m_View.getCenter().x -
        m_View.getSize().x / 2;
    startPosition.y = m_View.getCenter().y -
        m_View.getSize().y / 2;

    Vector2f scale;
    scale.x = m_View.getSize().x;
    scale.y = m_View.getSize().y;

    canvas[m_VertexStartIndex].position = startPosition;
    canvas[m_VertexStartIndex + 1].position =
        startPosition + Vector2f(scale.x, 0);
    canvas[m_VertexStartIndex + 2].position =
        startPosition + scale;
    canvas[m_VertexStartIndex + 3].position =
        startPosition + Vector2f(0, scale.y);


    if (m_IsMiniMap)
    {
        if (m_View.getSize().x <
            MAX_WIDTH && m_Position->width > 1)
        {
            m_View.zoom(m_Position->width);
        }
        else if (m_View.getSize().x >
            MIN_WIDTH && m_Position->width < 1)
        {
            m_View.zoom(m_Position->width);
        }
    }

    m_Window->setView(m_View);

    // Draw the time UI but only in the main camera
    if (!m_IsMiniMap)
    {
        m_Text.setString(std::to_string(m_Time));
        m_Text.setPosition(
            m_Window->mapPixelToCoords(Vector2i(5, 5)));
        m_Window->draw(m_Text);
    }

    // Draw the main canvas
    m_Window->draw(canvas, m_Texture);
}
