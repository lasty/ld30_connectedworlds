
#include "font/text.h"

#include "font/font.h"
#include "sdl/renderer.h"
#include "sdl/surface.h"

#include "sdl/headers.h"

#include <stdexcept>

Text::Text()
{
	//Nothing to do, leaves a blank texture, blank string, no width/height
}


Text::Text(const sdl::Renderer &rend, Font &font, const std::string &str)
: renderer(&rend), font(&font)
{
	SetText(str);
}


void Text::SetText(const std::string &newstr)
{
	if (str == newstr) return;  //don't redraw the same string
	str = newstr;

	if ( renderer == nullptr or font == nullptr)
	{
		throw std::logic_error("null pointers");
	}

	width = font->GetStringWidth(str);
	height = font->GetStringHeight(str);

	if (width == 0 or height == 0) return;

	sdl::Surface surf{width, height};

	surf.SetBlend(false);

	int x=0;
	int y=font->GetFace().GetBaseline();

	for (char ch : str)
	{
		Glyph &g = font->GetGlyph(ch);
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


	texture = sdl::Texture{*renderer, surf};

	texture.SetBlend(true);
}

void Text::RenderBox(const sdl::Renderer &rend, int x, int y) const
{
	//texture.SetBlend(false);
	SDL_SetRenderDrawBlendMode(rend.GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rend.GetRenderer(), 0, 0, 0, 0x33);

	int b=5;
	SDL_Rect rect{x-b, y-b, GetWidth()+2*b, GetHeight()+box_bottom_offset};
	SDL_RenderFillRect(rend.GetRenderer(), &rect);

	SDL_SetRenderDrawBlendMode(rend.GetRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(rend.GetRenderer(), 255, 255, 255, 255);

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

	if (box)
	{
		RenderBox(rend, r.x, r.y);
	}

	if (shadow)
	{
		SDL_SetTextureColorMod(texture.GetTexture(), 0, 0, 0);
		SDL_SetTextureAlphaMod(texture.GetTexture(), 128);
		SDL_Rect sr{r.x + shadow, r.y + shadow, r.w, r.h};

		rend.Copy(texture, nullptr, &sr);

		//texture.SetBlend(true);
		//SDL_SetRenderDrawBlendMode(rend.GetRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureColorMod(texture.GetTexture(), 255, 255, 255);
		SDL_SetTextureAlphaMod(texture.GetTexture(), 255);
	}

	rend.Copy(texture, nullptr, &r);
}

void Text::Render(int x, int y) const
{
	if (renderer)
	{
		Render(*renderer, x, y);
	}
	else
	{
		throw std::logic_error("Text::Render(x,y) - renderer not set");
	}
}
