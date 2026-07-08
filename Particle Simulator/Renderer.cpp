#include "Renderer.h"

void Render(sf::RenderWindow& window, std::vector<Particle>& particles, float ppm)
{

    for (Particle& particella : particles)
    {
        // 1. IL PONTE GRAFICO: Trasformiamo i metri in pixel prima di disegnare
        particella.forma.setPosition({ particella.posizione.x * ppm, particella.posizione.y * ppm });

        // 2. DISEGNO: Diciamo alla finestra di renderizzare la forma
        window.draw(particella.forma);
    }


}
