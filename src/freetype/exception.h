#ifndef FREETYPE_EXCEPTION_H
#define FREETYPE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace freetype
{

class Exception : public std::runtime_error
{
public:
	Exception(int code, const std::string &funcname);

	const char* what() const noexcept override { return message.c_str(); }

private:
	std::string message;
};


} // namespace freetype


#endif // FREETYPE_EXCEPTION_H

