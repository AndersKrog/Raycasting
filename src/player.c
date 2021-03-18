#include "player.h"

player_t player = {
	.x = MAP_NUM_ROWS * TILE_SIZE / 2,
	.y = MAP_NUM_COLS * TILE_SIZE / 2,
	.width = 5,
	.height = 5,
	.turnDirection = 0,
	.walkDirection = 0,
	.rotationAngle = PI / 2,
	.walkSpeed = 100,
	.turnSpeed = 45 * (PI / 180)
};

void movePlayer(float deltaTime) {
	player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
	float moveStep = player.walkDirection * player.walkSpeed * deltaTime;

	float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
	float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;
	// wallcoll

	if (!mapHasWallAt(newPlayerX, newPlayerY)) {
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}

void renderPlayer(void) {
	/*
	SDL_SetRenderDrawColor(renderer,255,0,0,255);
	SDL_Rect playerRect = {
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		player.width * MINIMAP_SCALE_FACTOR,
		player.height * MINIMAP_SCALE_FACTOR
	};
	SDL_RenderFillRect(renderer, &playerRect);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(
		renderer,
		MINIMAP_SCALE_FACTOR * player.x,
		MINIMAP_SCALE_FACTOR * player.y,
		MINIMAP_SCALE_FACTOR * player.x + cos(player.rotationAngle) * 40,
		MINIMAP_SCALE_FACTOR * player.y + sin(player.rotationAngle) * 40
	);
	*/
}

