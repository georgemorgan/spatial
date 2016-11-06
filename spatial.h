#ifndef __spatial_h__
#define __spatial_h__

#include <SDL2/SDL.h>

/* The window size. */
#define WIDTH 640
#define HEIGHT 480

/* Color macros. */
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

/* How far the player steps. */
#define SP_WALK_AMOUNT 0.1

#define FPS 60

/* Describes the location of and viewing angles of a camera. */
extern struct _camera { double x, y, z; double tx, ty, tz; } spc;

/* A point in 3D space. */
struct _p3d { double x, y, z; };

/* A point int 2D space. */
struct _p2d { double x, y; };

/* The main render loop. */
void sp_render(void);
/* Draws a line to the screen. */
void sp_line(int x1, int y1, int x2, int y2, int r, int g, int b);

/* Maps a range of values. */
double sp_map(double x, double in_min, double in_max, double out_min, double out_max);

/* Input functions. */
void sp_w(void);
void sp_a(void);
void sp_s(void);
void sp_d(void);
void sp_up(void);
void sp_down(void);
void sp_left(void);
void sp_right(void);

#endif
