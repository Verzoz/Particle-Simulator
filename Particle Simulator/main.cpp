#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>




struct Particle
{
    sf::CircleShape forma; // Raggio
    sf::Vector2f posizione;
    sf::Vector2f velocita;
};







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

    int numeroInizialeParticelle = 1000;
    float spaziaturaTraParticelle = 0.01f; // 10mm
    float inizioX = 0.10f;
    float inizioY = 0.05f; // Corretto a 5cm in base al tuo commento
    float larghezzaZonaSpawn = 0.40f;

    // ATTENZIONE: Questo calcola il numero di COLONNE, non l'altezza. Deve essere un intero (int)
    int colonne = larghezzaZonaSpawn / spaziaturaTraParticelle;

    // I cicli in C++ partono RIGOROSAMENTE da 0
    for (int i = 0; i < numeroInizialeParticelle; i++)
    {
        Particle p; // Oppure Goccia, dipende come hai chiamato la struct

        p.forma.setRadius(0.002f * ppm);
        p.forma.setOrigin({ 0.002f * ppm, 0.002f * ppm }); // Allinea il centro

        // CALCOLO A GRIGLIA
        int c = i % colonne; // Asse X = Modulo (Ciclo continuo)
        int r = i / colonne; // Asse Y = Divisione (Scaglioni)

        // ASSEGNAZIONE FISICA IN METRI
        p.posizione = sf::Vector2f(
            inizioX + (c * spaziaturaTraParticelle),
            inizioY + (r * spaziaturaTraParticelle)
        );

        p.velocita = sf::Vector2f(0.0f, 0.0f);
        p.forma.setFillColor(sf::Color::Blue);

        particles.push_back(p);
    }






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

        // update di ogni particella nell' array

        for (Particle& particella : particles)
        {


            float areaFisicaX = window.getView().getSize().x / ppm;
            float areaFisicaY = window.getView().getSize().y / ppm;
            float diametroFisico = 0.004f; // 4mm totali, dato che il raggio è 0.002f





            // Facciamo lavorare la gravità:
            particella.velocita.y += gravita * dt;

            // Aggiorniamo la posizione per la velocità corrente per far muovere le particelle:
            particella.posizione.x += particella.velocita.x * dt;
            particella.posizione.y += particella.velocita.y * dt;



            // Logica per la collisione con i bordi dello schermo

            // Muro Sinistro
            if (particella.posizione.x < 0.0f)
            {
                particella.posizione.x = 0.0f;
                particella.velocita.x = -(particella.velocita.x * (1.0f - energyDissipationFactor));
            }

            // Muro Destro
            if (particella.posizione.x > areaFisicaX - diametroFisico)
            {
                particella.posizione.x = areaFisicaX - diametroFisico;
                particella.velocita.x = -(particella.velocita.x * (1.0f - energyDissipationFactor));
            }

            // Muro Sopra
            if (particella.posizione.y < 0.0f)
            {
                particella.posizione.y = 0.0f;
                particella.velocita.y = -(particella.velocita.y * (1.0f - energyDissipationFactor));
            }

            // Muro Sotto
            if (particella.posizione.y > areaFisicaY - diametroFisico)
            {
                particella.posizione.y = areaFisicaY - diametroFisico;
                particella.velocita.y = -(particella.velocita.y * (1.0f - energyDissipationFactor));
            }

            // IL PONTE GRAFICO
            // Questa è l'unica riga in cui la fisica (metri) viene tradotta in grafica (pixel).
            // Si esegue alla fine del loop per ogni particella, dopo aver risolto tutti i possibili urti.
            particella.forma.setPosition({ particella.posizione.x * ppm, particella.posizione.y * ppm });

        }
        








        
        
        






        //RENDER

        window.clear(sf::Color::Black);

        // Draw things for the current frame in between 'clear' & 'display'


        // renderizziamo tutte le particelle
        for (auto& particella : particles)
        {   
            window.draw(particella.forma);
        }




        window.display();
    }
    

    return 0;
}