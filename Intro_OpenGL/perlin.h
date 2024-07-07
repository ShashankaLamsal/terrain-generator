#ifndef PERLIN_H
#define PERLIN_H

#include <glm/glm.hpp>

// generate a 2D Perlin noise value at a given position
//float perlinBase(float x,float y);

// generate Perlin noise with multiple octaves
float perlin(float x, float y, int octaves, float persistence, float ampMultiplier);

#endif 
