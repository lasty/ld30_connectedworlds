
#include "sdl/exception.h"

#include "sdl/headers.h"

#include <iostream>
#include <sstream>


namespace sdl
{

Exception::Exception(const std::string &function_name)
: runtime_error(function_name)
{
	std::ostringstream err;

	err << function_name << " failed: " << SDL_GetError();

	message = err.str();

	std::cerr << message << std::endl;
}



} // namespace sdl
