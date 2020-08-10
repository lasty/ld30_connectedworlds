#ifndef SDL_HEADERS_H
#define SDL_HEADERS_H


// Include the SDL headers

#ifdef __INTELLISENSE__
#define USE_SDL2_IMAGE
#define USE_SDL2_MIXER
#endif

#include <SDL.h>


#ifdef USE_SDL2_IMAGE
	#include <SDL_image.h>
#endif


#ifdef USE_SDL2_MIXER
	#include <SDL_mixer.h>
#endif


// SDL redefines main on windows
#ifdef __WIN32__
#undef main
#endif


#endif // SDL_HEADERS_H

