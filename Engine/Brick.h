#pragma once
#include "Rectf.h"
#include "Graphics.h"


class Brick
{public:
	Brick(Vec2 start, float width, float height, Color c);
	void Draw(Graphics &gfx);
	Rectf Get_Shrinked() const; //container of the brick after applying padding
	void Draw_with_padding(Graphics &gfx);
	//void Does_Ball_Colloides(Rectf &rtg.);
private:
	Color color;
	Rectf Rect;
	const float padding=1.0f;
	bool isDestroyed = false;
};