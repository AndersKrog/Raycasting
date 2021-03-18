#include "ray.h"

ray_t rays[NUM_RAYS];

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void normalizeAngle(float* angle) {
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0) {
		*angle = TWO_PI + *angle;
	}
}

void castRay(float rayAngle, int stripId) {
	normalizeAngle(&rayAngle);

	bool isRayFacingDown = rayAngle > 0 && rayAngle < PI;
	bool isRayFacingUp = !isRayFacingDown;

	bool isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	bool isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	//Horizontal Ray-grid intersection
	int foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	//find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	//find the x-coordinate of the closest horizontal grid intersection
	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	// calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// increment xstep and ystep till we find a wall
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY)) {
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck)) {
			foundHorzWallHit = true;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			break;	// helst ikke
		}
		else {
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	//##################################
	//Vertical Ray-grid intersection
	//##################################
	int foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	//find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	//find the y-coordinate of the closest horizontal grid intersection
	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	// calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	// increment xstep and ystep till we find a wall
	while (isInsideMap(nextVertTouchX, nextVertTouchY)) {
		float yToCheck = nextVertTouchY;
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck)) {
			foundVertWallHit = true;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));

			break;
		}
		else {
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}
	// Calculate both horizontal and vertical hit distances and choose the shortest
	float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY) : INT_MAX;
	float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY) : INT_MAX;

	if (vertHitDistance < horzHitDistance) {
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].wallHitContent = vertWallContent;
		rays[stripId].wasHitVertical = true;
	}
	else {
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].wallHitContent = horzWallContent;
		rays[stripId].wasHitVertical = false;

	}
	rays[stripId].rayAngle = rayAngle;
}

void castAllRays(void) {
	// start first ray half of our FOV

	//float rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

	for (int col = 0; col < NUM_RAYS; col++) {

		float angle = player.rotationAngle + atan((col - NUM_RAYS / 2) / DIST_PROJ_PLANE);
		castRay(angle, col);
	}
}

void renderRays(void) {
	for (int i = 0; i < NUM_RAYS; i++) {
		drawLine(
			player.x * MINIMAP_SCALE_FACTOR,
			player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFFFF0000
		);
	}
}
