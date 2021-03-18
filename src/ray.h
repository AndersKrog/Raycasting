#ifndef RAY_H
#define RAY_H

#include <limits.h>
#include <stdbool.h>
#include "./defs.h"
#include "./player.h"
#include "./graphics.h"


void normalizeAngle(float* angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);

void castRay(float rayAngle, int stripId);
void castAllRays(void);
void renderRays(void);

typedef struct {
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;
	int wallHitContent;
} ray_t;

extern ray_t rays[NUM_RAYS];

#endif