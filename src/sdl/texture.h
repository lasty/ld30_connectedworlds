#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H


#include <string>

struct SDL_Texture;

namespace sdl
{


class Renderer;
class Surface;


class Texture
{
public:
	Texture();
	Texture(const Renderer &rend, int width, int height);
	Texture(const Renderer &rend, const Surface &surface);
	Texture(const Renderer &rend, const std::string &image_filename);
	~Texture();


	//Block copy, implement move
	Texture(const Texture &copy) = delete;
	Texture(Texture &&move);
	Texture& operator=(const Texture &copy) = delete;
	Texture& operator=(Texture &&move);


private:
	SDL_Texture * texture = nullptr;
	unsigned width = 0;
	unsigned height = 0;

	void QueryTextureSize();



public:

	SDL_Texture * GetTexture() const { return texture; }

	unsigned GetWidth() const { return width; }
	unsigned GetHeight() const { return height; }

	void SetBlend(bool blend);
};


} // namespace sdl


#endif // SDL_TEXTURE_H

