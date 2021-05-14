#pragma once
#include "Rectf.h"
#include "Graphics.h"
#include "Vec2.h"
#include "ball.h"


class Brick
{public:
	Brick(Vec2 start, float width, float height, Color c);
	void Draw(Graphics &gfx);
	Rectf Get_Shrinked() const; //container of the brick after applying padding
	void Draw_with_padding(Graphics &gfx);
	bool Colloides_With_Ball(Ball &ball);
private:
	Color color;
	Rectf Rect;
	const float padding=1.0f;
	bool isDestroyed = false;
};