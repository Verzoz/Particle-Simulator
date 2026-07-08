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

    // Creamo la view della simulazione in 4k
    sf::View Simulazione(sf::FloatRect({ 0.0f, 0.0f }, { 3840.0f, 2160.0f } ));


    // Impostiamo la window che "Guarda" la view fisica appena creata
    window.setView(Simulazione);



    // VARIABILI GENERICHE
    float gravita = 9.81f;
    float energyDissipationFactor = 0.1f;

    // Pixel per Metro: serve per convertire le misure della simulazione in metri/secondo invece che pixel/secondo
    float ppm = 3180.0f; // 1 metro = 3180 px

    sf::Vector2f areaSimulazione(3840.0f, 2160.0f);

    // Orologio per rendere tutto indipendente dal framerate
    sf::Clock orologio;



    // Creo una particella rossa
    sf::CircleShape particella(0.002f * ppm); // 0.002 metri di raggio, cioè 2 mm
    particella.setFillColor(sf::Color(46, 129, 246));
       


    // Posizione iniziale della Particella
    particella.setPosition({ (areaSimulazione.x / 2) - (particella.getRadius())  ,   (areaSimulazione.y / 2) - (particella.getRadius()) });

    // Velocità iniziale della particella
    sf::Vector2f velocita(0.0f, 0.0f);






    // Run loop
    while (window.isOpen())
    {

        // Misuriamo il tempo tra un frame e l altro e lo salviamo in dt per rendere tutta la fisica indipendente dal framerate
        float dt = orologio.restart().asSeconds();


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

        // Facciamo agire la gravità
        velocita.y += gravita * dt;

        
        // Facciamo muovere la particella
        particella.move(velocita * dt * ppm);

        // Leggiamo dove si trova la particella
        sf::Vector2f pos = particella.getPosition();



        // Logica per la collisione con i bordi dello schermo

        
        if (pos.x < 0.0f) // Muro Sinistro
        {
            particella.setPosition({ 0.0f, pos.y });
            velocita.x = - ( velocita.x * ( 1.0f - energyDissipationFactor) ) ;
        }

        if (pos.x > areaSimulazione.x - (particella.getRadius() * 2.0f)) // Muro Destro
        {
            particella.setPosition({ areaSimulazione.x - (particella.getRadius() * 2.0f), pos.y });
            velocita.x = - ( velocita.x * ( 1.0f - energyDissipationFactor) );
        }

        if (pos.y < 0.0f) // Muro Sopra
        {
            particella.setPosition({ pos.x, 0.0f });
            velocita.y = - ( velocita.y * ( 1.0f - energyDissipationFactor ) );
        }

        if (pos.y > areaSimulazione.y - (particella.getRadius() * 2.0f)) // Muro Sotto
        {
            particella.setPosition({ pos.x, areaSimulazione.y - (particella.getRadius() * 2.0f) });
            velocita.y = - ( velocita.y * ( 1.0f - energyDissipationFactor ) );
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