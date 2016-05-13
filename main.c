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

typedef struct _vertex {
	float x, y, z;
} vertex;

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
						break;
					case SDLK_RIGHT:
						break;
					case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
					default:
						break;
				}
			}

			/* Clear the screen. */
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			/* ~~~ RENDERING BEGIN ~~~ */

			vertex cube[] = {
				{ 0, 0, 0 }, { 1, 0, 0 },
				{ 1, 1, 0 }, { 0, 1, 0 },
				{ 0, 0, 1 }, { 1, 0, 1 },
				{ 1, 1, 1 }, { 0, 1, 1 },
			};

			/* Obtain the center of the screen, and use it as the origin. */
			uint32_t cx = WIDTH / 2, cy = HEIGHT / 2;

			/* Obtain the x and y location of the mouse. */
			int mx, my;
			SDL_GetMouseState(&mx, &my);

			/* Map the mouse position to the input range of sin and cosine. */
			float tx = map(mx, 0, WIDTH, -M_PI_2, M_PI_2);
			float sin_tx = sin(tx), cos_tx = cos(tx);
			float ty = map(my, 0, WIDTH, -1, 1);
			float sin_ty = sin(ty), cos_ty = cos(ty);

			/* Iterate through the verticies, transforming them one at a time. */
			for (int v = 0; v < (sizeof(cube) / sizeof(vertex)); v ++) {
				/* Make the edges longer. */
				cube[v].x *= LENGTH, cube[v].y *= LENGTH, cube[v].z *= LENGTH;

				/* Transform the X and Y coordinates to rotate around the Z axis. */
				cube[v].x = cube[v].y * cos_tx - cube[v].x * sin_tx;
				cube[v].y = cube[v].x * cos_tx + cube[v].y * sin_tx;

				/* Transform the X and Y coordinates to rotate around the Y axis. */
//				cube[v].x = cube[v].x * cos_ty - cube[v].z * sin_ty;
//				cube[v].y = cube[v].z * cos_ty + cube[v].x * sin_ty;

				/* Transform the X and Y coordinates to rotate around the Y axis. */
				cube[v].x += cube[v].z;
				cube[v].y += cube[v].z;
			}

			/* Draw the vertices. */
			SDL_SetRenderDrawColor(renderer, GREEN, 255);
			int total = (sizeof(cube) / sizeof(vertex));
			for (int v = 0; v < total; v ++) {
				for (int r = v; r < total; r ++){
					line(renderer, cx + cube[v].x, cy + cube[v].y, cx + cube[r].x, cy + cube[r].y, GREEN);
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
