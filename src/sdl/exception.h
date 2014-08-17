#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace sdl
{


class Exception : public std::runtime_error
{
public:
	Exception(const std::string &function_name);

	const char* what() const noexcept override { return message.c_str(); }

private:
	std::string message;
};


} // namespace sdl


#endif // SDL_EXCEPTION_H
