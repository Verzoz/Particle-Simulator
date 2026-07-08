#include "Spawner.h"

void SpawnParticles(std::vector<Particle>& particles, int numParticelle, float ppm)
{
    float spaziaturaTraParticelle = 0.01f; // 10mm
    float inizioX = 0.10f;
    float inizioY = 0.05f; // Corretto a 5cm in base al tuo commento
    float larghezzaZonaSpawn = 0.40f;

    //Questo calcola il numero di COLONNE
    int colonne = larghezzaZonaSpawn / spaziaturaTraParticelle;

    // I cicli in C++ partono RIGOROSAMENTE da 0
    for (int i = 0; i < numParticelle; i++)
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
}
