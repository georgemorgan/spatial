#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

#define LENGTH 100

/* Describes the location of and viewing angles of a camera. */
struct _camera { float x, y, z, tx, ty; };

/* A point in 3D space. */
struct _p3d { float x, y, z; };

/* A point int 2D space. */
struct _p2d { float x, y; };

void line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int r, int g, int b) {
	
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {

	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}

int main(int argc, char *argv[]) {

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO)) {
		return EXIT_FAILURE;
	}

	/* Create an SDL window. */
	SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		SDL_Quit();
		return EXIT_FAILURE;
	}

	/* Create an SDL renderer. */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	/* Clear the renderer. */
	SDL_RenderClear(renderer);

	/* ~~~ APPLICATION BEGIN ~~~ */

	/* Create an SDL_Event to listen for a quit request. */
	SDL_Event event;

	/* Previous mouse positions. */
	int pmx, pmy;
	pmx = pmy = 0;

	/* Create the camera. */
	struct _camera camera = { 0, 0, 0, 0, 0 };

	/* Obtain the center of the screen, and use it as the origin. */
	struct _p2d origin = { WIDTH / 2, HEIGHT / 2};

	/* Draw the screen in a loop. */
	while (1) {
		
		/* Read the input buffer. */
		while (SDL_WaitEvent(&event)) {

			/* We have received a signal to quit. */
			if (event.type == SDL_QUIT) {
				goto quit;
			}

			/* We have received a key press. */
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						camera.x -= 5;
						break;
					case SDLK_RIGHT:
						camera.x += 5;
						break;
					case SDLK_UP:
						camera.z += 5;
						break;
					case SDLK_DOWN:
						camera.z -= 5;
						break;
					default:
						break;
				}
			}

			/* Clear the screen. */
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			/* ~~~ RENDERING BEGIN ~~~ */

			struct _p3d cube[] = {
				{ 50, 50, 50 }, { 100, 50, 50 },
				{ 100, 100, 50 }, { 50, 100, 50 },
				{ 50, 50, 100 }, { 100, 50, 100 },
				{ 100, 100, 100 }, { 50, 100, 100 },
			};
			uint32_t vertices = (sizeof(cube) / sizeof(struct _p3d));
			struct _p2d projection[vertices];

			/* Obtain the x and y location of the mouse. */
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			/* Skip rendering if nothing has changed. */
			//if (mx == pmx && my == pmy) continue;
			/* Save the new position. */
			pmx = mx, pmy = my;



			/* Map the mouse position to the input range of -1 to 1 for the output of sin and cosine. */
			float tx = map(mx, 0, WIDTH, 0, 2 * M_PI);
			float stx = sin(tx), ctx = cos(tx);
			float ty = map(my, 0, WIDTH, 0, 2 * M_PI);
			float sty = sin(ty), cty = cos(ty);

			/* Calculate the viewing angles of the camera. */

			printf("tx: %f, stx: %f, ctx: %f\n", tx, stx, ctx);
			printf("ty: %f, sty: %f, cty: %f\n", ty, sty, cty);

			/* Iterate through the verticies, transforming them one at a time. */
			for (int v = 0; v < vertices; v ++) {
				/* Make the edges longer. */

				/* Transform the X and Y coordinates to rotate around the X axis. */
//				cube[v].x = cube[v].y * ctx - cube[v].z * stx;
				cube[v].y = cube[v].z * ctx + cube[v].y * stx;

				/* Transform the X and Y coordinates to rotate around the Y axis. */
				cube[v].x = cube[v].x * cty - cube[v].z * sty;
//				cube[v].y = cube[v].z * cty + cube[v].x * sty;

				projection[v].x = (camera.z * (cube[v].x - camera.x)) / (camera.z + cube[v].z) + camera.x;
				projection[v].y = (camera.z * (cube[v].y - camera.y)) / (camera.z + cube[v].z) + camera.y;

			}

			/* Draw the vertices. */
			for (int v = 0; v < vertices; v ++) {
				for (int r = v; r < vertices; r ++){
					line(renderer, origin.x + projection[v].x, origin.y + projection[v].y, origin.x + projection[r].x, origin.y + projection[r].y, v * 100, r * 200, 255);
				}
			}

			/* ~~~ RENDERING END ~~~ */

			SDL_RenderPresent(renderer);
			
		}
				
	}

	/* ~~~ APPLICATION END ~~~ */

quit:

	/* Clean up after ourselves by destroying that which we have created. */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return EXIT_SUCCESS;
	
}
