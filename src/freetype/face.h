#ifndef FREETYPE_FACE_H
#define FREETYPE_FACE_H


#include "freetype/headers.h"
#include "freetype/library.h"

#include <stdint.h>
#include <string>



namespace freetype
{


class Face
{
public:
	//Face();
	Face(const std::string &font_filename, int font_size);
	~Face();

	//Block copy and move
	Face(const Face &copy) = delete;
	Face(Face &&move) = delete;
	Face& operator=(const Face &copy) = delete;
	Face& operator=(Face &&move) = delete;

private:
	freetype::Library library;
	FT_Face face = nullptr;

	int pitch = 0;  //current pitch (stride) of bitmap
	int font_size = 0;

	void SetSize(int font_size); // Should only be called once by constructor

public:
	// Loads a new glyph into the render slot.  All previous values are clobbered.
	void LoadAndRender(wchar_t ch);

	// Query functions for the currently rendered glyph..

	// Bitmap data
	int GetBitmapWidth() const;
	int GetBitmapHeight() const;
	uint8_t GetPixel(int x, int y) const;

	// X and Y offset positions
	int GetBearingX() const;
	int GetBearingY() const;

	// Horizontal Advance to next glyph
	int GetAdvance() const;

	// Vertical offsets
	int GetLineHeight() const;
	int GetBaseline() const;

};


} // namespace freetype

#endif // FREETYPE_FACE_H

