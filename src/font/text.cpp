
#include "font/text.h"

#include "font/font.h"
#include "sdl/renderer.h"
#include "sdl/surface.h"

#include "sdl/headers.h"


Text::Text()
{
	//Nothing to do, leaves a blank texture, blank string, no width/height
}


Text::Text(const sdl::Renderer &rend, Font &font, const std::string &str)
{
	SetText(rend, font, str);
}


void Text::SetText(const sdl::Renderer &rend, Font &font, const std::string &newstr)
{
	if (str == newstr) return;  //don't redraw the same string
	str = newstr;

	width = font.GetStringWidth(str);
	height = font.GetStringHeight(str);

	if (width == 0 or height == 0) return;

	sdl::Surface surf{width, height};

	surf.SetBlend(false);

	int x=0;
	int y=font.GetFace().GetBaseline();


	for (char ch : str)
	{
		Glyph &g = font.GetGlyph(ch);
		if (not g.blank)
		{
			const sdl::Surface &s = g.GetSurface();
			SDL_Rect dest;
			dest.x=x + g.bearingx;
			dest.y=y - g.bearingy;
			dest.w=g.width;
			dest.h=g.height;
			surf.Blit(s, nullptr, &dest);
		}
		x += g.advance;
	}


	texture = sdl::Texture{rend, surf};

	texture.SetBlend(true);
}


void Text::Render(const sdl::Renderer &rend, int x, int y) const
{
	SDL_Rect r;

	if (x < 0)
	{
		r.x = rend.GetWidth() - width + x;
	}
	else
	{
		r.x = x;
	}

	if (y < 0)
	{
		r.y = rend.GetHeight() - height + y;
	}
	else
	{
		r.y = y;
	}


	r.w = width;
	r.h = height;

	rend.Copy(texture, nullptr, &r);
}

