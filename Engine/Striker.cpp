#include "Striker.h"

Striker::Striker(const Vec2 & Centre, float width, float height, Vec2 velocity, Color c)
	:centre(Centre),
	velocity(velocity),
	color(c),
	width(width),
	height(height)
{
	
}

bool Striker::Hit_Ball(Ball & b)
{
	const Rectf &ball_Rect = b.get_Container();
	const Vec2 &ball_velocity = b.Peek_Velocity();
	const Vec2 &ball_centre = b.Peek_Centre();
	Rectf container = Get_Container();
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
			b.Add_Velocity(velocity*movement*0.25);//add velocit in x direction
		}
		else
		{
			if (ball_velocity.x - velocity.x*movement> 0 && (y_left_boundary > container.top) && (y_left_boundary < container.bottom))
			{
				b.ReboundX();
				b.displaceX(container.left - ball_Rect.right);
				b.displaceY(y_left_boundary - ball_centre.y);
				b.Add_Velocity(velocity*movement);
			}
			else if (ball_velocity.x - velocity.x*movement < 0 && (y_right_boundary > container.top) && (y_right_boundary < container.bottom))
			{
				b.ReboundX();
				b.displaceX(container.right - ball_Rect.left);
				b.displaceY(y_right_boundary - ball_centre.y);
				b.Add_Velocity(velocity*movement);
			}
		}
		return true;
	}
	return false;
}

void Striker::Touched_Wall(Rectf & Wall)
{
	Rectf container = Get_Container();
	if (container.right > Wall.right)
		centre.x += Wall.right - container.right;
	if (container.left < Wall.left)
		centre.x += Wall.left - container.left;
	if (container.top < Wall.top)
		centre.y += Wall.top - container.top;
	if (container.bottom > Wall.bottom)
		container.Displaced(Vec2(Wall.bottom - container.bottom, 0));
}

void Striker::Update(Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
		movement = right;
	else 
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		movement = left;
	}
	else
	{
		movement = rest;
	}
	centre += velocity * dt* movement;
}

void Striker::Draw(Graphics & gfx)
{
	Rectf container = Get_Container();

	//width of wing
	float width_of_wings = (container.right - container.left) / 10;
	//Draw left wing
	gfx.DrawRect(int(container.left), int(container.top), int(container.left + width_of_wings), int(container.bottom), Colors::Magenta);
	//Draw centre striker
	gfx.DrawRect(int(container.left+ width_of_wings+1), int(container.top), int(container.right-width_of_wings), (int)container.bottom, color);
	
	//Draw right wing
	gfx.DrawRect( int(container.right-width_of_wings+1),int(container.top), int(container.right), int(container.bottom), Colors::Magenta);

}
void Striker::Recentre(float x)
{
	centre.x = x;
}

Rectf Striker::Get_Container()
{
	Rectf R=  Rectf();
	R.Draw_from_centre(centre, width, height);
	return R;
}