
#include "sdl/mixer.h"

#include "sdl/headers.h"
#include "sdl/exception.h"
#include "sdl/sound.h"


namespace sdl
{


Mixer::Mixer()
{
	int ret = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_AllocateChannels(16);  //Default of 8 seems a little low

	if (ret < 0)
	{
		throw sdl::Exception("Mix_OpenAudio()");
	}
}


Mixer::~Mixer()
{
	Mix_CloseAudio();
}


void Mixer::Quit()
{
	//Stops all channels.. we are about to free sound sample memory (called from App)
	Mix_HaltChannel(-1);
}


int Mixer::PlaySound(Sound &sound, int channel)
{
	int ch = Mix_PlayChannel(channel, sound.GetChunk(), 0);

	if (ch < 0)
	{
		//prints an error message, but does not throw
		sdl::Exception("Mix_PlayChannel()");
	}

	return ch;
}


} // namespace sdl
