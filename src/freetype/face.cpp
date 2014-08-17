
#include "freetype/face.h"

#include "freetype/headers.h"
#include "freetype/exception.h"


namespace freetype
{


Face::Face(const std::string &font_filename, int font_size)
{
	constexpr int index = 0;

	int err = FT_New_Face(library.GetLibrary(), font_filename.c_str(), index, &face);

	if (err)
	{
		throw freetype::Exception(err, "FT_New_Face()");
	}

	SetSize(font_size);
}


Face::~Face()
{
	FT_Done_Face(face);
}


void Face::SetSize(int font_size)
{
	int err = FT_Set_Char_Size(face, font_size*64, font_size*64, 96, 96);
	if (err)
	{
		throw freetype::Exception(err, "FT_Set_Char_Size()");
	}

	this->font_size = font_size;
}


void Face::LoadAndRender(wchar_t ch)
{
	int err = FT_Load_Char(face, ch, FT_LOAD_DEFAULT);
	if (err)
	{
		throw freetype::Exception(err, "FT_Load_Char()");
	}

	if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
	{
		int err = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
		if (err)
		{
			throw freetype::Exception(err, "FT_Render_Glyph");
		}

	}

	//setup pitch variable for Get Pixel
	pitch = abs(face->glyph->bitmap.pitch);
}


int Face::GetBitmapWidth() const
{
	return face->glyph->bitmap.width;
}


int Face::GetBitmapHeight() const
{
	return face->glyph->bitmap.rows;
}


uint8_t Face::GetPixel(int x, int y) const
{
	if (x < 0 or y < 0 or x >= GetBitmapWidth() or y >= GetBitmapHeight())
		throw std::logic_error("Face::GetPixel : position out of range");

	const FT_Bitmap &bitmap = face->glyph->bitmap;

	const unsigned index = (y * pitch) + x;
	return bitmap.buffer[index];
}


int Face::GetBearingX() const
{
	return face->glyph->bitmap_left;
}


int Face::GetBearingY() const
{
	return face->glyph->bitmap_top;
}


int Face::GetAdvance() const
{
	return face->glyph->advance.x / 64.0f;
}


int Face::GetLineHeight() const
{
	return face->size->metrics.height / 64.0f;
}


int Face::GetBaseline() const
{
	return font_size;
}



} // namespace freetype
