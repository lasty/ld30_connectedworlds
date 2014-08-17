#ifndef FONT_FONT_H
#define FONT_FONT_H


#include "freetype/face.h"
#include "font/glyph.h"

#include <string>
#include <map>


//XXX so far this only caters for ASCII text.
//TODO add UTF-8 support


class Font
{
public:
	Font(const std::string &font_filename, int font_size);

private:
	freetype::Face face;
	std::map<wchar_t, Glyph> glyphs;

public:
	const freetype::Face& GetFace() { return face; }

	bool HasGlyph(wchar_t ch) const;
	Glyph& GetGlyph(wchar_t ch);

	const sdl::Surface & GetGlyphSurface(wchar_t ch);

	int GetStringWidth(const std::string str);
	int GetStringHeight(const std::string str);
};


#endif // FONT_FONT_H
