#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "spatial.h"

SDL_Renderer *_sp_renderer;

void sp_line(int x1, int y1, int x2, int y2, int r, int g, int b) {
	SDL_SetRenderDrawColor(_sp_renderer, r, g, b, 255);
	SDL_RenderDrawLine(_sp_renderer, x1 + WIDTH/2, y1 + HEIGHT/2, x2 + WIDTH/2, y2 + HEIGHT/2);
}

double sp_map(double x, double in_min, double in_max, double out_min, double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char *argv[]) {

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO)) {
		return EXIT_FAILURE;
	}

	/* Create an SDL window. */
	SDL_Window *window = SDL_CreateWindow("Spatial Engine", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		goto quit;
	}

	/* Create an SDL renderer. */
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (!renderer) {
		goto quit;
	}
	/* Set the main renderer. */
	_sp_renderer = renderer;

	/* Clear the renderer. */
	SDL_RenderClear(renderer);

	/* ~~~ APPLICATION BEGIN ~~~ */

	/* Create an SDL_Event to listen for a quit request. */
	SDL_Event event;

	/* Draw the screen in a loop. */
	while (1) {

		uint32_t start_time = SDL_GetTicks();

		/* Read the input buffer. */
		if (SDL_WaitEvent(&event)) {

			/* We have received a signal to quit. */
			if (event.type == SDL_QUIT) {
				goto quit;
			}

			/* We have received a key press. */
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						sp_left();
						break;
					case SDLK_RIGHT:
						sp_right();
						break;
					case SDLK_UP:
						sp_up();
						break;
					case SDLK_DOWN:
						sp_down();
						break;
					case SDLK_w:
						sp_w();
						break;
					case SDLK_a:
						sp_a();
						break;
					case SDLK_s:
						sp_s();
						break;
					case SDLK_d:
						sp_d();
						break;
					default:
						break;
				}
			}

		}

		/* Clear the screen. */
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		/* ~~~ RENDERING BEGIN ~~~ */

		sp_render();

		/* ~~~ RENDERING END ~~~ */

		SDL_RenderPresent(renderer);

//		if ((1000/FPS)>(SDL_GetTicks()-start_time)) {
//			SDL_Delay((1000/FPS)-(SDL_GetTicks()-start_time));
//		}

	}

	/* ~~~ APPLICATION END ~~~ */

quit:

	/* Clean up after ourselves by destroying that which we have created. */
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	
	return EXIT_SUCCESS;
	
}
