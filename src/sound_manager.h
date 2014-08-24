#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H


#include "sdl/mixer.h"
#include "sdl/sound.h"

#include "utils.h"

#include <iostream>

class SoundManager
{
private:
	sdl::Mixer &mixer;
public:
	SoundManager(sdl::Mixer &mixerref) : mixer(mixerref) { }

private:
	sdl::Sound beep1 { FindFile("beep1.wav") };
	sdl::Sound beep2 { FindFile("beep2.wav") };
	sdl::Sound beep3 { FindFile("beep3.wav") };

	sdl::Sound explosion1 { FindFile("explosion1.wav") };
	sdl::Sound explosion2 { FindFile("explosion2.wav") };
	sdl::Sound explosion3 { FindFile("explosion3.wav") };

	sdl::Sound hit1 { FindFile("hit1.wav") };
	sdl::Sound hit2 { FindFile("hit2.wav") };
	sdl::Sound hit3 { FindFile("hit3.wav") };
	sdl::Sound hit4 { FindFile("hit4.wav") };

	sdl::Sound laser1 { FindFile("laser1.wav") };
	sdl::Sound laser2 { FindFile("laser2.wav") };
	sdl::Sound laser3 { FindFile("laser3.wav") };

	sdl::Sound pickup1 { FindFile("pickup1.wav") };
	sdl::Sound pickup2 { FindFile("pickup2.wav") };
	sdl::Sound pickup3 { FindFile("pickup3.wav") };

	sdl::Sound powerup1 { FindFile("powerup1.wav") };
	sdl::Sound powerup2 { FindFile("powerup2.wav") };

public:
	void GoToWorld(int i)
	{
		if (i==0) mixer.PlaySound(powerup2);
		else mixer.PlaySound(powerup1);
	}

	void Beep()
	{
		int i = random_int(1, 3);
		if (i==1) mixer.PlaySound(beep1);
		else if (i==2) mixer.PlaySound(beep2);
		else mixer.PlaySound(beep3);

		//std::cout << "Beep " << i << std::endl;
	}

	void Explosion()
	{
		int i = random_int(1, 3);
		if (i==1) mixer.PlaySound(explosion1);
		else if (i==2) mixer.PlaySound(explosion2);
		else mixer.PlaySound(explosion3);

		//std::cout << "Explosion " << i << std::endl;
	}

	void Hit()
	{
		int i = random_int(1, 4);
		if (i==1) mixer.PlaySound(hit1);
		else if (i==2) mixer.PlaySound(hit2);
		else if (i==3) mixer.PlaySound(hit3);
		else mixer.PlaySound(hit4);

		//std::cout << "Hit " << i << std::endl;
	}

	void Laser()
	{
		int i = random_int(1, 3);
		if (i==1) mixer.PlaySound(laser1);
		else if (i==2) mixer.PlaySound(laser2);
		else mixer.PlaySound(laser3);

		//std::cout << "Laser " << i << std::endl;
	}


	void Pickup()
	{
		int i = random_int(1, 3);
		if (i==1) mixer.PlaySound(pickup1);
		else if (i==2) mixer.PlaySound(pickup2);
		else mixer.PlaySound(pickup3);

		//std::cout << "Pickup " << i << std::endl;
	}


};




#endif // SOUND_MANAGER_H
