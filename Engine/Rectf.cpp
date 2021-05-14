#include "Rectf.h"
#include <assert.h>


Rectf::Rectf(const float left, const float right,const float top,const float bottom)
:
	left(left),
	right(right),
	top(top),
	bottom(bottom)
{
	assert(left <= right);
	assert(top <= bottom);
}

Rectf::Rectf(const Vec2 & start, const Vec2 & end)
	:Rectf(start.x, end.x, start.y, end.y)
{
}

Rectf::Rectf(const Vec2 & start, float width, float height)
:Rectf(start, start+ Vec2(width, height))
{
}

bool Rectf::Overlaps_With(const Rectf & Rect)
{
	return (Rect.left < right) && (left < Rect.right) && (top < Rect.bottom) && (Rect.top < bottom);
}

void Rectf::draw_solid(Graphics & gfx, Color color)
{
	gfx.DrawRect(left, top, right, bottom, color);
}

void Rectf::Draw_from_centre(Vec2 centre, float width, float height)
{
	*this=Rectf(centre.x-width/2, centre.x+width/2, centre.y-height/2, centre.y+height/2); /// check for optimization
}

void Rectf::Displaced(Vec2 displacement)
{
	left+= displacement.x;
	right += displacement.x;
	top += displacement.y;
	bottom += displacement.y;
}
