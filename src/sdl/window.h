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

	//Block copy and move
	Window(const Window &copy) = delete;
	Window(Window &&move) = delete;
	Window& operator=(const Window &copy) = delete;
	Window& operator=(Window &&move) = delete;


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
