
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
};

int main()
{

	TestApp app("warmup30", 400, 300);

	app.Run();

}
