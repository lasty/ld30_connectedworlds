
#include "sdl/window.h"

#include "sdl/headers.h"
#include "sdl/exception.h"

namespace sdl
{


Window::Window(const std::string &title, unsigned width, unsigned height)
: title(title)
, width(width)
, height(height)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 50, width, height, flags);

	if (window == nullptr)
	{
		throw sdl::Exception("SDL_CreateWindow()");
	}
}


Window::~Window()
{
	if (window)
	{
		SDL_DestroyWindow(window);
	}
}


void Window::SetTitle(const std::string &newtitle)
{
	title = newtitle;
	SDL_SetWindowTitle(window, title.c_str());
}


} // namespace sdl
