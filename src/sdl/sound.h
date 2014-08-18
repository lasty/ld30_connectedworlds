#ifndef SDL_SOUND_H
#define SDL_SOUND_H


#include <string>

struct Mix_Chunk;


namespace sdl
{


class Sound
{
public:
	Sound(const std::string &sound_filename);
	~Sound();


	//Block copy, implement move
	Sound(const Sound &copy) = delete;
	Sound(Sound &&move);
	Sound& operator=(const Sound &copy) = delete;
	Sound& operator=(Sound &&move);


private:
	Mix_Chunk * chunk = nullptr;

public:
	Mix_Chunk * GetChunk() const { return chunk; }

};


} // namespace sdl


#endif // SDL_SOUND_H

