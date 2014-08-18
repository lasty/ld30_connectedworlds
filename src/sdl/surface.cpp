
#include "sdl/surface.h"

#include "sdl/headers.h"

#include "sdl/exception.h"

#include <stdint.h>


namespace sdl
{


Surface::Surface(int width, int height)
: width(width)
, height(height)
{
	uint32_t rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);

	if (surface == nullptr)
	{
		throw sdl::Exception("SDL_CreateRGBSurface()");
	}
}


Surface::Surface(const std::string &image_filename)
{
	surface = IMG_Load(image_filename.c_str());
	if (surface == nullptr)
	{
		throw sdl::Exception("IMG_Load()");
	}

	width = surface->w;
	height = surface->h;
}



Surface::~Surface()
{
	if (surface)
	{
		SDL_FreeSurface(surface);
	}
}


Surface::Surface(Surface &&move)
{
	std::swap(width, move.width);
	std::swap(height, move.height);
	std::swap(surface, move.surface);
}


Surface& Surface::operator=(Surface &&move)
{
	std::swap(width, move.width);
	std::swap(height, move.height);
	std::swap(surface, move.surface);

	return *this;
}


void Surface::Lock()
{
	if (SDL_MUSTLOCK(surface))
	{
		int ret = SDL_LockSurface(surface);
		if (ret < 0)
		{
			throw sdl::Exception("SDL_LockSurface()");
		}
	}
}


void Surface::Unlock()
{
	if (SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}


void Surface::SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (x < 0 or y < 0 or (unsigned)x >= width or (unsigned)y >= height)
	{
		throw std::logic_error("SetPixel value out of range");
	}

	uint8_t * pixels = reinterpret_cast<uint8_t*>(surface->pixels);

	pixels += (surface->pitch * y) + ( 4 * x );

	pixels[0] = r;
	pixels[1] = g;
	pixels[2] = b;
	pixels[3] = a;
}


void Surface::Blit(const Surface &surf, SDL_Rect *src, SDL_Rect *dest)
{
	int ret = SDL_BlitSurface(surf.surface, src, surface, dest);
	if (ret < 0)
	{
		throw sdl::Exception("SDL_BlitSurface()");
	}
}


void Surface::SetBlend(bool blend)
{
	const auto mode = blend ? SDL_BLENDMODE_BLEND : SDL_BLENDMODE_NONE;

	SDL_SetSurfaceBlendMode(surface, mode);
}


} // namespace sdl
