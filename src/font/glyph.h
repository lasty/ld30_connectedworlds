#ifndef FONT_GLYPH_H
#define FONT_GLYPH_H


#include "freetype/face.h"
#include "sdl/surface.h"

#include <memory>

class Glyph
{
public:
	Glyph(freetype::Face &face, const wchar_t ch);

	bool blank = false;
	int width = 0;
	int height = 0;

	int bearingx = 0;
	int bearingy = 0;

	int advance = 0;

private:
	std::unique_ptr<sdl::Surface> surf;

public:
	const sdl::Surface & GetSurface() const { return *surf; }
};


#endif // FONT_GLYPH_H

