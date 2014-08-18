#ifndef SDL_MIXER_H
#define SDL_MIXER_H

namespace sdl
{

class Sound;


class Mixer
{
public:
	Mixer();
	~Mixer();

	//Block copy and move
	Mixer(const Mixer &copy) = delete;
	Mixer(Mixer &&move) = delete;
	Mixer& operator=(const Mixer &copy) = delete;
	Mixer& operator=(Mixer &&move) = delete;

	int PlaySound(Sound &sound, int channel = -1);

};


} // namespace sdl


#endif // SDL_MIXER_H

