#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class InputReceiver
{
private:
    vector<Event> mEvents;

public:
    void addEvent(Event event);
    vector<Event>& getEvents();
    void clearEvents();
};
