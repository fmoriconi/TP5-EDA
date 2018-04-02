#pragma once

typedef enum { QUIET, WALKING_RIGHT, WALKING_LEFT, JMP_WARMUP, JUMPING, FALLING } wormState_t;
typedef enum { WORM1 = 1, WORM2 = 2 } wormEnum_t;
typedef enum { LEFT, RIGHT, UP, NO_MOV } wormMoves_t;

#define DISPLAY_HEIGHT 696
#define DISPLAY_WIDTH 1920
#define WQTY 2 //Cantidad de worms

#define FPS 50.0
#define MOVE_FPS 10.0
