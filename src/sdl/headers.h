#ifndef SDL_HEADERS_H
#define SDL_HEADERS_H


// Include the SDL headers


#ifdef __APPLE__
	// MacOSX requires Framework prefix
	#include <SDL2/SDL.h>
#else
	#include <SDL.h>
#endif


#ifdef USE_SDL2_IMAGE
	#include <SDL_image.h>  //TODO: MacOSX might be different
#endif


#ifdef USE_SDL2_MIXER
	#include <SDL_mixer.h>  //TODO: MacOSX might be different
#endif


// SDL redefines main on windows
#ifdef __WIN32__
#undef main
#endif


#endif // SDL_HEADERS_H

