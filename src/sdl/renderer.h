#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Point;

#include <stdint.h>


namespace sdl
{

class Window;
class Texture;


class Renderer
{
public:
	Renderer(Window &window);
	~Renderer();

	Renderer(const Renderer &copy) = delete;
	Renderer(Renderer &&move) = delete;
	Renderer& operator=(const Renderer &copy) = delete;
	Renderer& operator=(Renderer &&move) = delete;

private:
	SDL_Renderer *renderer = nullptr;
	Window &window;


public:
	SDL_Renderer * GetRenderer() const { return renderer; }

	void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;
	void Clear() const;

	void Copy(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest) const;
	void CopyEx(const Texture &texture, const SDL_Rect *src, const SDL_Rect *dest
		, double angle, const SDL_Point* center) const;

	void Present() const;

	unsigned GetWidth() const;
	unsigned GetHeight() const;
};



} // namespace sdl


#endif // SDL_RENDERER_H

