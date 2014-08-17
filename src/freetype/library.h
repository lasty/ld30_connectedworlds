#ifndef FREETYPE_LIBRARY_H
#define FREETYPE_LIBRARY_H

#include "freetype/headers.h"

namespace freetype
{

class Library
{
public:
	Library();
	~Library();


	//Block copies and moves
	Library(const Library &copy) = delete;
	Library(Library &&move) = delete;
	Library& operator=(const Library &copy) = delete;
	Library& operator=(Library &&move) = delete;

private:
	FT_Library library = nullptr;

public:
	FT_Library GetLibrary() const { return library; }

};


} // namespace freetype


#endif // FREETYPE_LIBRARY_H

