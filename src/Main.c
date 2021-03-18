#include <stdio.h>
#include <SDL.h>
#include <stdint.h>
#include <stdbool.h>

#include "./defs.h"
#include "./textures.h"
#include "./map.h"
#include "./ray.h"
#include "./player.h"
//#include "./graphics.h"
#include "./wall.h"


// global variables
bool game_is_running = false;

int ticksLastFrame = 0;


void processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		game_is_running = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			game_is_running = false;
		if (event.key.keysym.sym == SDLK_UP)
			player.walkDirection = +1;
		if (event.key.keysym.sym == SDLK_DOWN)
			player.walkDirection = -1;
		if (event.key.keysym.sym == SDLK_RIGHT)
			player.turnDirection = +1;
		if (event.key.keysym.sym == SDLK_LEFT)
			player.turnDirection = -1;
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_UP)
			player.walkDirection = 0;
		if (event.key.keysym.sym == SDLK_DOWN)
			player.walkDirection = 0;
		if (event.key.keysym.sym == SDLK_RIGHT)
			player.turnDirection = 0;
		if (event.key.keysym.sym == SDLK_LEFT)
			player.turnDirection = 0;
		break;
	}
}

SDL_AudioSpec wav_spec;
Uint32 wav_length;
Uint8* wav_buffer;

void playMusic() {

	/* Load the WAV */
	if (SDL_LoadWAV("./sound/enemy.wav", &wav_spec, &wav_buffer, &wav_length) == NULL) {
		fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
	}
	else {
		/* Do stuff with the WAV data, and then... */
		// open audio device

		SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
		SDL_PauseAudio(0);

		//play
		int success = SDL_QueueAudio(deviceId, wav_buffer, wav_length);
		SDL_PauseAudioDevice(deviceId, 0);

	}
}

void setup() {
	playMusic();
}

void update() {
	// brug ikke while, da det optager cpu'en

	// compute how long we have untill reaching the target frame time in milliseconds
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);
	// only delay execution if runnning too fast
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH) {
		SDL_Delay(timeToWait);
	}
	
	//deltatime in seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	// store the milliseconds of the current frame
	ticksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castAllRays();
}


void render() {
	clearColorBuffer(0xFF777777);
	generateWallProjection();

	// display minimap
	renderMap();
	//renderPlayer();
	renderRays();

	renderColorBuffer();
}

int main(int argc, char* args[]){

	game_is_running = initialize_window();

	setup();

	while (game_is_running) {
		processInput();
		update();
		render();
	}
	destroyWindow();
	//freeWallTextures();
	SDL_FreeWAV(wav_buffer);
	return 0;
}