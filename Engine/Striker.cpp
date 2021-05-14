#include "Striker.h"

Striker::Striker(const Vec2 & StartPosition, float width, float height, Vec2 velocity, Color c)
	:container(StartPosition, width, height),
	velocity(velocity),
	color(c)
{
	
}

bool Striker::hit_ball(Ball & b)
{
	if (container.Overlaps_With(b.get_Container()))
	{
		b.ReboundY();
		return true;
	}
}

void Striker::touched_wall(Rectf & Wall)
{
	if (container.right > Wall.right)
		container.Displaced(Vec2(Wall.right - container.right, 0));
	if (container.left < Wall.left)
		container.Displaced(Vec2(Wall.left - container.left, 0));
	if (container.top < Wall.top)
		container.Displaced(Vec2(Wall.top - container.top, 0));
	if (container.bottom > Wall.bottom)
		container.Displaced(Vec2(Wall.bottom - container.bottom, 0));
}

void Striker::update(Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_RIGHT) || kbd.KeyIsPressed(VK_LEFT))
	{
		velocity.x = -(velocity.x);
		container.Displaced(velocity*dt);
	}
}

void Striker::Draw(Graphics & gfx)
{
	container.draw_solid(gfx,color);
}

