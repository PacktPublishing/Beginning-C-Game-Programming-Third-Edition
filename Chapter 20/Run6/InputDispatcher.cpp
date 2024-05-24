#include "InputDispatcher.h"

InputDispatcher::InputDispatcher(RenderWindow* window)
{
    m_Window = window;
}

void InputDispatcher::dispatchInputEvents()
{
    sf::Event event;
    while (m_Window->pollEvent(event))
    {        
        for (const auto& ir : m_InputReceivers)
        {
            ir->addEvent(event);
        }
    }
}

void InputDispatcher::registerNewInputReceiver(InputReceiver* ir)
{
    m_InputReceivers.push_back(ir);
}
