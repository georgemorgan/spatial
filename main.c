#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define WIDTH 1920
#define HEIGHT 1200

#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

#define SDL_GetSurfacePixel(surface, x, y) (uint32_t *)(surface -> pixels + (y * surface -> pitch + (x * surface -> format -> BytesPerPixel)))

void line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int r, int g, int b) {
	
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	
}

int main(int argc, char *argv[]) {

	/* Initialize SDL. */
	if (SDL_Init(SDL_INIT_VIDEO)) {
		return EXIT_FAILURE;
	}

	/* Create an SDL window. */
	SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
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
	
	uint32_t rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
	#else
	rmask = 0x000000ff; gmask = 0x0000ff00; bmask = 0x00ff0000; amask = 0xff000000;
	#endif

	/* Create an SDL surface. */
	SDL_Surface *surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, rmask, gmask, bmask, amask);
	if (!renderer) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

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

			line(renderer, 10, 10, 20, 20, GREEN);

			/* ~~~ RENDERING END ~~~ */

			SDL_RenderPresent(renderer);
			
		}
				
	}

	/* ~~~ APPLICATION END ~~~ */

quit:

	/* Clean up after ourselves by destroying that which we have created. */
	SDL_FreeSurface(surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return EXIT_SUCCESS;
	
}