#include "Physics.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void UpdatePhysics(
    sf::RenderWindow& window, 
    std::vector<Particle>& particles, 
    float EnergyDissipationFactor, 
    float ppm,
    float gravita,
    float dt
)
{

    float tolleranzaSuolo = 0.0001f;

    for (Particle& particella : particles)
    {


        float areaFisicaX = window.getView().getSize().x / ppm;
        float areaFisicaY = window.getView().getSize().y / ppm;
        float diametroFisico = 0.004f; // 4mm totali, dato che il raggio è 0.002f


        
        // 1. CONTROLLO STATO: La particella è già a terra e ferma?
        bool aTerra = (particella.posizione.y >= (areaFisicaY - diametroFisico) - tolleranzaSuolo)
            && (std::abs(particella.velocita.y) < 0.05f);

        // 2. APPLICAZIONE FORZE: Applichi la gravità SOLO se NON è a terra
        if (!aTerra)
        {
            particella.velocita.y += gravita * dt;
        }
        else
        {
            particella.velocita.y = 0.0f; // Blindiamo la velocità a zero
            particella.velocita.x = 0.0f;
        }


        // 3. MOVIMENTO:


        // Aggiorniamo la posizione per la velocità corrente per far muovere le particelle:
        particella.posizione.x += particella.velocita.x * dt;
        particella.posizione.y += particella.velocita.y * dt;



        // Logica per la collisione con i bordi dello schermo

        // Muro Sinistro
        if (particella.posizione.x < 0.0f)
        {
            particella.posizione.x = 0.0f;
            particella.velocita.x = -(particella.velocita.x * (1.0f - EnergyDissipationFactor));
        }

        // Muro Destro
        if (particella.posizione.x > areaFisicaX - diametroFisico)
        {
            particella.posizione.x = areaFisicaX - diametroFisico;
            particella.velocita.x = -(particella.velocita.x * (1.0f - EnergyDissipationFactor));
        }

        // Muro Sopra
        if (particella.posizione.y < 0.0f)
        {
            particella.posizione.y = 0.0f;
            particella.velocita.y = -(particella.velocita.y * (1.0f - EnergyDissipationFactor));
        }

        // Muro Sotto
        if (particella.posizione.y > areaFisicaY - diametroFisico)
        {
            particella.posizione.y = areaFisicaY - diametroFisico;

            // Calcoliamo la nuova velocità dopo il rimbalzo
            float nuovaVelocitaY = -(particella.velocita.y * (1.0f - EnergyDissipationFactor));

            // SOGLIA DI TOLLERANZA (Deadzone)
            // Se la velocità di rimbalzo è inferiore a 0.05 metri al secondo (5 cm/s), 
            // consideriamo la particella ferma a terra e azzeriamo la velocità.
            if (std::abs(nuovaVelocitaY) < 0.05f)
            {
                particella.velocita.y = 0.0f;
                particella.velocita.x = 0.0f; // Azzera anche l'eventuale tremolio orizzontale
            }
            else
            {
                particella.velocita.y = nuovaVelocitaY;
            }
        }

        // IL PONTE GRAFICO
        // Questa è l'unica riga in cui la fisica (metri) viene tradotta in grafica (pixel).
        // Si esegue alla fine del loop per ogni particella, dopo aver risolto tutti i possibili urti.
        particella.forma.setPosition({ particella.posizione.x * ppm, particella.posizione.y * ppm });

    }
}
