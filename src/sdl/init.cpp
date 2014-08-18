
#include "sdl/init.h"

#include "sdl/exception.h"

#include "sdl/headers.h"


namespace sdl
{

Init::Init()
{
	auto flags = SDL_INIT_VIDEO;

#ifdef USE_SDL2_MIXER
	flags |= SDL_INIT_AUDIO;
#endif

	int ret = SDL_Init(flags);

	if (ret < 0)
	{
		throw sdl::Exception("SDL_Init()");
	}

#ifdef USE_SDL2_MIXER
	int mixflags = 0;
	int mixinit = Mix_Init(mixflags);
	if ((mixinit & mixflags) != mixflags)
	{
		throw sdl::Exception("Mix_Init()");
	}
#endif

}


Init::~Init()
{

#ifdef USE_SDL2_MIXER
	Mix_Quit();
#endif

	SDL_Quit();
}

} // namespace sdl

