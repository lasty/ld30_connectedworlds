
#include "font/font.h"


Font::Font(const std::string &font_filename, int font_size)
: face(font_filename, font_size)
{

}


bool Font::HasGlyph(wchar_t ch) const
{
	auto it = glyphs.find(ch);
	return (it != glyphs.end());
}


Glyph& Font::GetGlyph(wchar_t ch)
{
	if (not HasGlyph(ch))
	{
		glyphs.emplace( std::make_pair( ch, Glyph(face, ch) ) );
	}

	return glyphs.at(ch);
}


const sdl::Surface & Font::GetGlyphSurface(wchar_t ch)
{
	Glyph &g = GetGlyph(ch);
	return g.GetSurface();
}


int Font::GetStringWidth(const std::string str)
{
	int width = 0;
	for (const char ch : str)
	{
		Glyph &g = GetGlyph(ch);
		width += g.advance;
	}

	return width;
}


int Font::GetStringHeight(const std::string str)
{
	return face.GetLineHeight();
}


