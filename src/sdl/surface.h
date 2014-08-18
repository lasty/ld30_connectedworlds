#ifndef SDL_SURFACE_H
#define SDL_SURFACE_H

#include <stdint.h>
#include <string>

struct SDL_Surface;
struct SDL_Rect;


namespace sdl
{

class Surface
{
public:
	Surface(int width, int height);
	Surface(const std::string &image_filename);
	~Surface();

	//Block copy, implement move
	Surface(const Surface &copy) = delete;
	Surface(Surface &&move);
	Surface& operator=(const Surface &copy) = delete;
	Surface& operator=(Surface &&move);

private:
	SDL_Surface * surface = nullptr;
	unsigned width = 0;
	unsigned height = 0;

public:
	SDL_Surface * GetSurface() const { return surface; }

	unsigned GetWidth() const { return width; }
	unsigned GetHeight() const { return height; }

	void Lock();
	void Unlock();

	void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void Blit(const Surface &surf, SDL_Rect *src, SDL_Rect *dest);

	void SetBlend(bool blend);
};


} // namespace sdl


#endif // SDL_SURFACE_H

