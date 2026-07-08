#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

struct Particle
{
    sf::CircleShape forma; // Raggio
    sf::Vector2f posizione;
    sf::Vector2f velocita;
};
