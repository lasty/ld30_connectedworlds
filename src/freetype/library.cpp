
#include "freetype/library.h"

#include "freetype/headers.h"
#include "freetype/exception.h"


namespace freetype
{


Library::Library()
{
	int err = FT_Init_FreeType(&library);

	if (err)
	{
		throw freetype::Exception(err, "FT_Init_FreeType()");
	}
}


Library::~Library()
{
	FT_Done_FreeType(library);
}


} // namespace freetype

