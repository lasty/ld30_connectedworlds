
#include "freetype/exception.h"

#include <iostream>
#include <sstream>


namespace freetype
{


Exception::Exception(int code, const std::string &funcname)
: runtime_error(funcname)
{
	std::ostringstream err;
	err << "Freetype function " << funcname << " filed with code " << code;

	message = err.str();

	std::cerr << message << std::endl;
}


} // namespace freetype
