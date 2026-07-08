#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Particle.h"
#include "Spawner.h"
#include "EventsHandler.h"
#include "Physics.h"
#include "Renderer.h"


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




    // Vettore che contiene tutte le particelle
    std::vector<Particle> particles;



    // Chiamiamo la funzione che fa Spawnare le Particelle iniziali
    int numeroInizialeParticelle = 1000;
    SpawnParticles(particles, numeroInizialeParticelle, ppm);





    // SIMULATION LOOP
    while (window.isOpen())
    {

        // Misuriamo il tempo tra un frame e l altro e lo salviamo in dt per rendere tutta la fisica indipendente dal framerate
        float dt = orologio.restart().asSeconds();



        // Chiamiamo la funzione che gestisce gli eventi
        EventsHandler(window);





        //UPDATE

        // update di ogni particella nell' array
        UpdatePhysics
        (
            window, 
            particles, 
            energyDissipationFactor, 
            ppm,
            gravita,
            dt
        );
        



        //RENDER

        window.clear(sf::Color::Black);

        // Draw things for the current frame in between 'clear' & 'display'
        Render(window, particles, ppm);

        window.display();
    }
    

    return 0;
}