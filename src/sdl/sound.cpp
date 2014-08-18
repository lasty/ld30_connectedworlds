
#include "sdl/sound.h"

#include "sdl/headers.h"
#include "sdl/exception.h"


namespace sdl
{


Sound::Sound(const std::string &sound_filename)
{
	chunk = Mix_LoadWAV(sound_filename.c_str());

	if (chunk == nullptr)
	{
		throw sdl::Exception("Mix_LoadWAV()");
	}
}


Sound::~Sound()
{
	if (chunk)
	{
		Mix_FreeChunk(chunk);
	}
}


Sound::Sound(Sound &&move)
{
	std::swap(chunk, move.chunk);
}


Sound& Sound::operator=(Sound &&move)
{
	std::swap(chunk, move.chunk);

	return *this;
}


} // namespace sdl
