#ifndef DEFS_H
#define DEFS_H

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

#define MAP_SIZE_X (MAP_NUM_COLS*TILE_SIZE)
#define MAP_SIZE_Y (MAP_NUM_ROWS*TILE_SIZE)
#define NUM_TEXTURES 8


#define MINIMAP_SCALE_FACTOR 0.125 

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 400

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define FOV_ANGLE (60 * (PI / 180))
#define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

#define NUM_RAYS WINDOW_WIDTH

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#endif 