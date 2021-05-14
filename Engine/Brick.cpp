#include "Brick.h"

Brick::Brick(Vec2 start, float width, float height, Color c)
	:Rect(start, width, height),
	color(c)
{

}

void Brick::Draw(Graphics & gfx)
{
	if (isDestroyed)
		return;
	Rect.draw_solid(gfx, color);
}

Rectf Brick::Get_Shrinked() const
{
	Rectf Shrinked = Rectf(Rect.left + padding, Rect.right - padding, Rect.top + padding, Rect.bottom - padding);
	return Shrinked;
}

void Brick::Draw_with_padding(Graphics & gfx)
{
	if (isDestroyed)
		return;
	Rectf shrinked_Rect = Get_Shrinked();
	shrinked_Rect.draw_solid(gfx, color);
}

bool Brick::Colloides_With_Ball(Ball & ball)
{
	if ((!isDestroyed) && Rect.Overlaps_With(ball.get_Container()))
	{
		ball.ReboundY();
		isDestroyed = true;
		return true;
    }
	return false;
}

