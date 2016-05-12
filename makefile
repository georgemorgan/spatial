output = main

find = $(shell which 'find')

cc = $(shell which 'clang')

sdlflags = $(shell sdl2-config --cflags --libs) -framework OpenGL

$(info $(sdlflags))

excludes = 

cfiles = $(shell $(find) . -name '*.c' $(foreach exclude, $(excludes), -not -name '$(exclude)'))

all:

	$(cc) -std=c99 $(sdlflags) $(cfiles) -o $(output)

clean:

	$(shell rm -rf $(shell $(find) . -name '*.o') $(output))
