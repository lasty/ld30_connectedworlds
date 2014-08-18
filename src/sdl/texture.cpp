
#include "sdl/texture.h"

#include "sdl/headers.h"
#include "sdl/exception.h"
#include "sdl/renderer.h"
#include "sdl/surface.h"

#include <string>

namespace sdl
{


Texture::Texture()
{

}


Texture::Texture(const Renderer &rend, int width, int height)
{
	uint32_t format = SDL_PIXELFORMAT_RGBA8888;
	int access = SDL_TEXTUREACCESS_STATIC;

	texture = SDL_CreateTexture(rend.GetRenderer(), format, access, width, height);

	if (texture == nullptr)
	{
		throw sdl::Exception("SDL_CreateTexture()");
	}

	QueryTextureSize();
}


Texture::Texture(const Renderer &rend, const Surface &surface)
{
	texture = SDL_CreateTextureFromSurface(rend.GetRenderer(), surface.GetSurface());

	if (texture == nullptr)
	{
		throw sdl::Exception("SDL_CreateTextureFromSurface()");
	}

	QueryTextureSize();
}


Texture::Texture(const Renderer &rend, const std::string &image_filename)
{
	sdl::Surface surf { image_filename };

	texture = SDL_CreateTextureFromSurface(rend.GetRenderer(), surf.GetSurface());

	if (texture == nullptr)
	{
		throw sdl::Exception("SDL_CreateTextureFromSurface()");
	}

	QueryTextureSize();
}


Texture::~Texture()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}


Texture::Texture(Texture &&move)
{
	std::swap(texture, move.texture);
	std::swap(width, move.width);
	std::swap(height, move.height);
}


Texture& Texture::operator=(Texture &&move)
{
	std::swap(texture, move.texture);
	std::swap(width, move.width);
	std::swap(height, move.height);

	return *this;
}


void Texture::QueryTextureSize()
{
	int w, h;
	int ret = SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	if (ret < 0)
	{
		throw sdl::Exception("SDL_QueryTexture()");
	}

	width = w;
	height = h;
}


void Texture::SetBlend(bool blend)
{
	if (blend)
	{
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	}
	else
	{
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
	}
}


} // namespace sdl
