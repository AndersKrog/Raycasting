#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include "./defs.h"
#include "graphics.h"


bool mapHasWallAt(float x, float y);
void renderMap(void);
int getMapAt(int i, int j);
bool isInsideMap(float nextTouchX, float nextTouchY);

#endif