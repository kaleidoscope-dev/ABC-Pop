#include "I_cWidget.h"


I_cWidget::I_cWidget()
{
 focus_ = false;
 render_bck_ = true;
}

I_cWidget::~I_cWidget()
{
}

void I_cWidget::SetPos(int x, int y, int w, int h)
{
 
 widget_rect_.x = x;
 widget_rect_.y = y;
 widget_rect_.w = w;
 widget_rect_.h = h;

}


void I_cWidget::RenderBackground(bool b)
{
	render_bck_ = b;
}


void I_cWidget::SetFocus(bool f)
{
 focus_ = f;
}

bool I_cWidget::GetFocus(void)
{
 return focus_;
}


void I_cWidget::HandleEvent(SDL_Event *event)
{

	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);
	SDL_Point pt = { x,y };
	if (SDL_PointInRect(&pt, &widget_rect_))
	{
	 focus_ = true;
	}
}

void I_cWidget::HandleEvent(AndUIn::ANDUIN_EVENT_TYPE type)
{
}


void I_cWidget::Draw()
{
 if (focus_)
    {
	 roundedRectangleRGBA(AndUIn::renderer_, widget_rect_.x+1, widget_rect_.y+1, widget_rect_.x + widget_rect_.w-1, widget_rect_.y + widget_rect_.h, 2, 0, 255, 0, 255);  // prvi sloj (pozadina)
	}

}






SDL_Texture *I_cWidget::vertgradient(SDL_Surface * surf, SDL_Color c1, SDL_Color c2)
{
	int y, width, height;
	Uint8 r, g, b;
	SDL_Rect dest;
	Uint32 pixelcolor;

	width = surf->w;
	height = surf->h;

	for (y = 0; y < height; y++)
	{
		r = (c2.r * y / height) + (c1.r * (height - y) / height);
		g = (c2.g * y / height) + (c1.g * (height - y) / height);
		b = (c2.b * y / height) + (c1.b * (height - y) / height);

		dest.x = 0;
		dest.y = y;
		dest.w = width;
		dest.h = 1;

		pixelcolor = SDL_MapRGB(surf->format, r, g, b);

		SDL_FillRect(surf, &dest, pixelcolor);
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(AndUIn::renderer_, surf);
	return tex;

}

