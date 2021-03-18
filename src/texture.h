#ifndef TEXTURES_H
#define TEXTURES_H
#include "upng.h"
#include "constants.h"
#include <stdint.h>

typedef struct {
	upng_t* upngTexture;
	int width;
	int height;
	uint32_t* texture_buffer;
} texture_t;

texture_t wallTextures[NUM_TEXTURES];

void loadWallTextures();

#endif

