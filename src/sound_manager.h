#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H


#include "sdl/mixer.h"
#include "sdl/sound.h"


class SoundManager
{
private:
	sdl::Mixer &mixer;
public:
	SoundManager(sdl::Mixer &mixerref) : mixer(mixerref) { }

private:
	sdl::Sound sound1 { FindFile("powerup.wav") };
	sdl::Sound sound2 { FindFile("beep.wav") };

public:
	void Powerup() { mixer.PlaySound(sound1); }
	void Beep() { mixer.PlaySound(sound2); }

};




#endif // SOUND_MANAGER_H
