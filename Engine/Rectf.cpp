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
	gfx.DrawRect(int(left),int(top), int(right), int(bottom), color);
}

void Rectf::draw_hollow(Graphics & gfx, Color color, float boundary_thick)
{
	//draw top boundary
	gfx.DrawRect(int(left), int(top), int(right), int(top - boundary_thick), color);
	//draw bottom boundary
	gfx.DrawRect(int(left), int(bottom), int(right), int(bottom + boundary_thick), color);
	//draw left boundary
	gfx.DrawRect(int(left), int(top), int(left-boundary_thick), int(bottom), color);
	//draw right boundary
	gfx.DrawRect(int(right) + int(boundary_thick), int(top), int(right), int(bottom), color);
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

const Vec2 Rectf::Get_Centre() const
{
	Vec2 centre((left + right) / 2, (top + bottom) / 2);
	return centre;
}