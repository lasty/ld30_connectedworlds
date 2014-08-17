
#include "font/glyph.h"


Glyph::Glyph(freetype::Face &face, const wchar_t ch)
{
	face.LoadAndRender(ch);

	width = face.GetBitmapWidth();
	height = face.GetBitmapHeight();

	bearingx = face.GetBearingX();
	bearingy = face.GetBearingY();

	advance = face.GetAdvance();

	if (width == 0 and height == 0)
	{
		blank = true;
		return;
	}

	surf.reset( new sdl::Surface(width, height) );
	surf->SetBlend(false);

	//create luminance/alpha image of glyph
	surf->Lock();
	for (int y=0; y<height; ++y)
	{
		for (int x=0; x<width; ++x)
		{
			auto grey = face.GetPixel(x,y);

			//luminance: completely white
			uint8_t r, g, b;
			r = g = b = 255;

			//alpha: greyscale value from freetype bitmap
			uint8_t a = grey;

			surf->SetPixel(x, y, r, g, b, a);
		}
	}
	surf->Unlock();
}



