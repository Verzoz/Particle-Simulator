#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>


int main()
{

    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Prima App");
    window.setVerticalSyncEnabled(true); // VSync attivato
    // window.setFramerateLimit(60);



    // Creo una particella rossa
    sf::CircleShape particella(20.0f);
    particella.setFillColor(sf::Color(46, 129, 246));

    
    sf::Vector2f pos = particella.getPosition();
    sf::Vector2u dimFinestra = window.getSize();


    // Posizione iniziale della Particella
    particella.setPosition({ ((float)dimFinestra.x / 2) - (particella.getRadius())  ,   ((float)dimFinestra.y / 2) - (particella.getRadius()) });

    // Velocità iniziale della particella
    sf::Vector2f velocita(22.0f, 22.0f);






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

        
        // Facciamo muovere la particella
        particella.move(velocita);

        // Leggiamo dove si trova la particella
        sf::Vector2f pos = particella.getPosition();



        // Logica per la collisione con i bordi dello schermo

        
        if (pos.x < 0.0f) // Muro Sinistro
        {
            particella.setPosition({ 0.0f, pos.y });
            velocita.x = -velocita.x;
        }

        if (pos.x > (float)dimFinestra.x - (particella.getRadius() * 2.0f)) // Muro Destro
        {
            particella.setPosition({ (float)dimFinestra.x - (particella.getRadius() * 2.0f), pos.y });
            velocita.x = -velocita.x;
        }

        if (pos.y < 0.0f) // Muro Sopra
        {
            particella.setPosition({ pos.x, 0.0f });
            velocita.y = -velocita.y;
        }

        if (pos.y > (float)dimFinestra.y - (particella.getRadius() * 2.0f)) // Muro Sotto
        {
            particella.setPosition({ pos.x, (float)dimFinestra.y - (particella.getRadius() * 2.0f) });
            velocita.y = -velocita.y;
        }
        
        






        //RENDER

        window.clear(sf::Color::Black);

        // Draw things for the current frame in between 'clear' & 'display'


        // renderizziamo la particella
        window.draw(particella);




        window.display();
    }
    

    return 0;
}