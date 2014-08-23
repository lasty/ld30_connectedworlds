#ifndef SDL_APP_H
#define SDL_APP_H


#include "sdl/init.h"
#include "sdl/window.h"
#include "sdl/renderer.h"
#include "sdl/mixer.h"

#include <string>
#include <memory>

struct SDL_KeyboardEvent;

namespace sdl
{


class App
{
public:
	App(const std::string title, unsigned width, unsigned height);
	virtual ~App();

private:
	sdl::Init init;
	sdl::Window window;

protected:
	sdl::Renderer renderer { window };
	sdl::Mixer mixer;

	bool running = false;
	long long lastframe_time = 0;
	int fps_framecount = 0;
	float fps_timer = 0.0f;

	void ProcessEvents();
	void Present();
	float GetDeltaTime();
	void FPSUpdate(float dt);
	void SetTitle(const std::string &newtitle) { return window.SetTitle(newtitle); }

public:
	void Run();
	void Quit();

	virtual void Update(float dt);
	virtual void Render() const;
	virtual void OnFPS(int fps_framecount);

	virtual void OnKey(SDL_KeyboardEvent &e, bool down);

	virtual void OnMouseButton(int x, int y, int but, bool down);
	virtual void OnMouseMove(int x, int y);

};


} // namespace sdl

#endif // SDL_APP_H
