#ifndef SDL_HEADERS_H
#define SDL_HEADERS_H


// Include the SDL headers


#ifdef __APPLE__
	// MacOSX requires Framework prefix
	#include <SDL2/SDL.h>
#else
	#include <SDL.h>
#endif


// SDL redefines main on windows
#ifdef __WIN32__
#undef main
#endif


#endif // SDL_HEADERS_H

