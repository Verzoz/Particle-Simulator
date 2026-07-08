#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Particle.h"


void UpdatePhysics(
    sf::RenderWindow& window,
    std::vector<Particle>& particles,
    float EnergyDissipationFactor,
    float ppm,
    float gravita,
    float dt
);