#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <string>

struct SDL_Window;

namespace sdl
{

class Window
{
public:
	Window(const std::string &title, unsigned width, unsigned height);
	~Window();

private:
	SDL_Window *window = nullptr;
	std::string title;
	unsigned width;
	unsigned height;

public:
	unsigned GetWidth() const { return width; }
	unsigned GetHeight() const { return height; }

	void SetTitle(const std::string &newtitle);
};


} // namespace sdl


#endif // SDL_WINDOW_H
