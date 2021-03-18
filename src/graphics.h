#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>
#include "./defs.h"
#include "./textures.h"

//header files for function prototypes, constants, new types

bool initializeWindow(void);
void destroyWindow(void);
void clearcolorBuffer(uint32_t color);
void renderColorBuffer(void);
void drawPixel(int x, int y, uint32_t color);
void drawRect(int x, int y,int width, int height, uint32_t color);
void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
void changeColorIntensity(uint32_t* color, float factor);

#endif