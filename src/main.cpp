
#include <iostream>

#include "sdl/app.h"

#include "font/font.h"
#include "font/text.h"
#include "sdl/surface.h"
#include "sdl/texture.h"

#include <sstream>

#define DATA_PATH "../data/"

class TestApp : public sdl::App
{
public:

	Font font1 { DATA_PATH "DroidSans.ttf", 16 };
	Text text1 { renderer, font1, "Hello World" };

	sdl::Surface sprite_surf { DATA_PATH "sprites.png" };
	sdl::Texture sprite_texture { renderer, sprite_surf };


	TestApp(int width, int height)
	: App("Warmup 30", width, height)
	{


	}


	void OnFPS(int fps) override
	{
		std::ostringstream ss;
		ss << "FPS: " << fps;

		SetTitle(ss.str());

		text1.SetText(renderer, font1, ss.str());
	}

	void Render() const override
	{
		renderer.SetColour(20, 30, 40, 255);
		renderer.Clear();

		renderer.Copy(sprite_texture, nullptr, nullptr);

		text1.Render(renderer, 5, 5);

	}

	void OnKey(SDL_KeyboardEvent &e, bool down) override
	{
		Quit();
	}
};


int main()
{

	TestApp app(400, 300);

	app.Run();

}
