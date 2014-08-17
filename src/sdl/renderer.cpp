
#include "sdl/renderer.h"

#include "sdl/headers.h"
#include "sdl/exception.h"
#include "sdl/window.h"
#include "sdl/texture.h"


namespace sdl
{


Renderer::Renderer(Window &window)
:window(window)
{
	uint32_t flags = SDL_RENDERER_ACCELERATED;

	renderer = SDL_CreateRenderer(window.GetWindow(), -1, flags);

	if (renderer == nullptr)
	{
		throw sdl::Exception("SDL_CreateRenderer()");
	}
}


Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}


void Renderer::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const
{
	SDL_SetRenderDrawColor(renderer, r,g, b, a);
}


void Renderer::Clear() const
{
	SDL_RenderClear(renderer);
}


void Renderer::Copy(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest) const
{
	SDL_RenderCopy(renderer, texture.GetTexture(), src, dest);
}


void Renderer::CopyEx(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest
	, double angle, const SDL_Point* center) const
{
	SDL_RenderCopyEx(renderer, texture.GetTexture(), src, dest, angle, center, SDL_FLIP_NONE);
}


void Renderer::Present() const
{
	SDL_RenderPresent(renderer);
}


unsigned Renderer::GetWidth() const
{
	return window.GetWidth();
}


unsigned Renderer::GetHeight() const
{
	return window.GetHeight();
}


} // namespace sdl

