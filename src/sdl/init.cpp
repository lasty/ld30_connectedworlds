
#include "sdl/init.h"

#include "sdl/exception.h"

#include "sdl/headers.h"


namespace sdl
{

Init::Init()
{
	int ret = SDL_Init(SDL_INIT_VIDEO);

	if (ret < 0)
	{
		throw sdl::Exception("SDL_Init()");
	}
}


Init::~Init()
{
	SDL_Quit();
}

} // namespace sdl

