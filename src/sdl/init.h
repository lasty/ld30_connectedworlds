#ifndef SDL_INIT_H
#define SDL_INIT_H


namespace sdl
{


class Init
{
public:
	Init();
	~Init();

	//Block copy and move
	Init(const Init& copy) = delete;
	Init(Init&& move) = delete;
	Init& operator=(const Init& copy) = delete;
	Init& operator=(Init&& move) = delete;
};


} // namespace sdl

#endif // SDL_INIT_H
