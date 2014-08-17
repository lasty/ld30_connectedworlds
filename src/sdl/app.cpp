
#include "sdl/app.h"


#include "sdl/headers.h"


namespace sdl
{


App::App(const std::string title, unsigned width, unsigned height)
: init()
, window(title, width, height)
{

}


App::~App()
{

}


void App::ProcessEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			Quit();
		}
		else if (event.type == SDL_KEYDOWN)
		{
			OnKey(event.key, true);
		}
		else if (event.type == SDL_KEYUP)
		{
			OnKey(event.key, false);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			OnMouseButton(event.button.x, event.button.y, event.button.button, true);
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			OnMouseButton(event.button.x, event.button.y, event.button.button, false);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			OnMouseMove(event.button.x, event.button.y);
		}

		//TODO add more event filters as appropriate
	}
}


void App::Present()
{
	renderer.Present();
}


float App::GetDeltaTime()
{
	long long this_time = SDL_GetTicks();

	float dt = (this_time - lastframe_time) / 1000.0f;

	lastframe_time = this_time;

	return dt;
}


void App::FPSUpdate(float dt)
{
	fps_framecount++;
	fps_timer += dt;

	if (fps_timer >= 1.0f)
	{
		OnFPS(fps_framecount);
		fps_timer -= 1.0f;
		fps_framecount = 0;
	}
}


void App::Run()
{
	lastframe_time = SDL_GetTicks(); //Init timers
	running = true;

	while(running)
	{
		ProcessEvents();

		float dt = GetDeltaTime();
		FPSUpdate(dt);
		Update(dt);

		Render();

		Present();
	}
}


void App::Quit()
{
	running = false;
}


void App::Update(float dt)
{

}


void App::Render() const
{

}


void App::OnFPS(int fps_framecount)
{

}


void App::OnKey(SDL_KeyboardEvent &e, bool down)
{

}


void App::OnMouseButton(int x, int y, int but, bool down)
{

}


void App::OnMouseMove(int x, int y)
{

}


} // namespace sdl

