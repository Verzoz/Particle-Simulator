#pragma once

#include <vector>

#include "Particle.h"

// Ritorna void, e prende l'array tramite l'indirizzo di memoria (&)
void SpawnParticles(std::vector<Particle>& particles, int numParticelle, float ppm);