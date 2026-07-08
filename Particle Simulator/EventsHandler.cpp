#include "EventsHandler.h"


// Per il momento controlliamo solo la chiusura
void EventsHandler(sf::RenderWindow& window)
{

    // Checks all the events triggered since the last iteration of the loop
    while (const std::optional event = window.pollEvent())
    {

        // Close request Handling
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

    }


}
