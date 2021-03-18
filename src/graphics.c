#include "graphics.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static uint32_t* colorBuffer = NULL;
static SDL_Texture* colorBufferTexture;


bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL. \n");
		return false;
	}
	SDL_DisplayMode display_mode;
	SDL_GetDisplayMode(0, 0, &display_mode);
	int fullScreenWidth = display_mode.w;
	int fullScreenHeight = display_mode.h;

	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		fullScreenWidth,
		fullScreenHeight,
		SDL_WINDOW_BORDERLESS
	);

	loadTextures();

	if (!window) {
		fprintf(stderr, "Error creating SDL window. \n");
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer. \n");
		return false;
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// allocate the amount of bytes in memory to hold colorbuffer
	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * (uint32_t)WINDOW_WIDTH * (uint32_t)WINDOW_HEIGHT);
	//colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	//colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

	return true;
}

void destroyWindow(void) {
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void clearColorBuffer(uint32_t color) {
	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
		colorBuffer[i] = color;
	}
}
void renderColorBuffer(void) {
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)(uint32_t)WINDOW_WIDTH * sizeof(uint32_t));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
void drawPixel(int x, int y, uint32_t color) {
	colorBuffer[WINDOW_WIDTH * y + x] = color;
}
void drawRect(int x, int y, int width, int height, uint32_t color){
	for (int i = x; i < x + width; i++) {
		for (int j = y; j < y + height; j++) {
			drawPixel(i, j, color);
		}
	}
}
void drawLine(int x0, int y0, int x1, int y1, uint32_t color) {
	int delta_x = x1 - x0;
	int delta_y = y1 - y0;

	int side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x): abs(delta_y);

	//how much to increment x and y each step 
	float x_inc = delta_x / (float)side_length;
	float y_inc = delta_y / (float)side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i <= side_length; i++) {
		drawPixel(round(current_x), round(current_y), color);

			current_x += x_inc;
			current_y += y_inc;
	}
};
void changeColorIntensity(uint32_t* color, float factor) {
	//bitwise operations to isolate colors
	uint32_t a = (*color & 0xFF000000);
	uint32_t r = (*color & 0x00FF0000) * factor;
	uint32_t g = (*color & 0x0000FF00) * factor;
	uint32_t b = (*color & 0x000000FF) * factor;

	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}
