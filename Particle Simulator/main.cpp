#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>


int main()
{

    sf::RenderWindow window(sf::VideoMode({1270, 720}), "Prima App");
    window.setVerticalSyncEnabled(true); // VSync attivato
    // window.setFramerateLimit(60);


    // Run loop
    while (window.isOpen())
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


        //UPDATE







        //RENDER

        window.clear(sf::Color::Black);

        // Draw things for the current frame in between 'clear' & 'display'

        window.display();
    }
    

    return 0;
}