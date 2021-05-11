#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
class Rectf
{
public:
	Rectf() = default;
	Rectf(const float left,const float right,const float top,const float bottom);
	Rectf(const Vec2 & start, const Vec2 & end);
	Rectf(const Vec2 & start, float width, float height);
	bool Overlaps_With(const Rectf& Rect);
	void draw_solid(Graphics & gfx, Color color);
  //void draw_hollow(Graphics &gfx, Color color, float boundary_thick);
	void Draw_from_centre(Vec2 centre, float width, float height);
public:
	float left;
	float right;
	float top;
	float bottom;

};