
#include <iostream>

#include "sdl/app.h"


#include <sstream>

class TestApp : public sdl::App
{
public:
	using App::App;

	void OnFPS(int fps) override
	{
		std::ostringstream ss;
		ss << "FPS: " << fps;

		SetTitle(ss.str());
	}

	void Render() const override
	{
		renderer.SetColour(20, 30, 40, 255);
		renderer.Clear();
	}

	void OnKey(SDL_KeyboardEvent &e, bool down) override
	{
		Quit();
	}
};


int main()
{

	TestApp app("warmup30", 400, 300);

	app.Run();

}
