#include "Striker.h"

Striker::Striker(const Vec2 & StartPosition, float width, float height, Vec2 velocity, Color c)
	:container(StartPosition, width, height),
	velocity(velocity),
	color(c)
{
	
}

bool Striker::Hit_Ball(Ball & b)
{
	const Rectf &ball_Rect = b.get_Container();
	const Vec2 &ball_velocity = b.Peek_Velocity();
	const Vec2 &ball_centre = b.Peek_Centre();
	 //calculating y-coordinate of intersection point of ball with left boundary of striker
	if (container.Overlaps_With(ball_Rect))
	{
		float y_left_boundary = ball_centre.y - ((ball_Rect.right - container.left)*ball_velocity.y / (ball_velocity.x));

		//calculating y-coordinate of intersection point of ball with right boundary
		float y_right_boundary = ball_centre.y - (ball_Rect.left - container.right)*ball_velocity.y / ball_velocity.x;

		//calculating x-coordinate of intersection point of ball  with top boundary
		float x_top_boundary = ball_centre.x - (ball_Rect.bottom - container.top)*ball_velocity.x / ball_velocity.y;

		if (ball_velocity.y > 0 && x_top_boundary > container.left && x_top_boundary < container.right)
		{
			b.ReboundY();
			b.displaceY(container.top - ball_Rect.bottom);
			b.displaceX(x_top_boundary - ball_centre.x);
		}
		else
		{
			if (ball_velocity.x > 0 && (y_left_boundary > container.top) && (y_left_boundary < container.bottom))
			{
				b.ReboundX();
				b.displaceX(container.left - ball_Rect.right);
				b.displaceY(y_left_boundary - ball_centre.y);
			}
			else if (ball_velocity.x < 0 && (y_right_boundary > container.top) && (y_right_boundary < container.bottom))
			{
				b.ReboundX();
				b.displaceX(container.right - ball_Rect.left);
				b.displaceY(y_right_boundary - ball_centre.y);
			}
		}
		return true;
	}
	return false;
}

void Striker::Touched_Wall(Rectf & Wall)
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

void Striker::Update(Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		container.Displaced(velocity*dt);
	}
	else 
	if (kbd.KeyIsPressed(VK_LEFT))
	{
	container.Displaced(velocity*(-dt));
	}
}

void Striker::Draw(Graphics & gfx)
{
	container.draw_solid(gfx,color);
}

