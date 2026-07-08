#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.h"

void Render(sf::RenderWindow& window, std::vector<Particle>& particles, float ppm);