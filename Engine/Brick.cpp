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
	const Rectf &ball_Rect = ball.get_Container();
	const Vec2 &ball_velocity = ball.Peek_Velocity();
	const Vec2 &ball_centre = ball.Peek_Centre();

	if ((!isDestroyed) && Rect.Overlaps_With(ball.get_Container()))
	{
		isDestroyed = true; //Destroy the object


		//calculating y-coordinate of intersection point of ball with left boundary
		float y_left_boundary = ball_centre.y - ((ball_Rect.right - Rect.left)*ball_velocity.y / (ball_velocity.x));

		//calculating y-coordinate of intersection point of ball with right boundary
		float y_right_boundary = ball_centre.y - (ball_Rect.left - Rect.right)*ball_velocity.y / ball_velocity.x;

		//calculating x-coordinate of intersection point of ball  with top boundary
		float x_top_boundary = ball_centre.x - (ball_Rect.bottom - Rect.top)*ball_velocity.x / ball_velocity.y;
		
		//calculating x-coordinate of intersection point of ball  with top boundary
		float x_bottom_boundary = ball_centre.x - (ball_Rect.top - Rect.bottom)*ball_velocity.x / ball_velocity.y;
		

		//checking if ball hits the left side of brick
		if (ball_velocity.x > 0 && y_left_boundary >= Rect.top && y_left_boundary <= Rect.bottom)
		{
			ball.ReboundX();
			ball.displaceX(Rect.left - ball_Rect.right);
			ball.displaceY(y_left_boundary - ball_centre.y);
		}
		else
			//checking if ball hits the right side of brick	
			if (ball_velocity.x < 0 && y_right_boundary >= Rect.top && y_right_boundary <= Rect.bottom)
			{
				ball.ReboundX();
				ball.displaceX(Rect.right - ball_Rect.left);
				ball.displaceY(y_right_boundary - ball_centre.y);
		     }
		
		//checking if ball hits the top side of brick
		if (ball_velocity.y > 0 && x_top_boundary >= Rect.left && x_top_boundary <= Rect.right)
		{
			ball.ReboundY();
			ball.displaceY(Rect.top - ball_Rect.bottom);
			ball.displaceX(x_top_boundary - ball_centre.x);
		}
		else
			//checking if ball hits the bottom side of brick	
			if (ball_velocity.y < 0 && x_bottom_boundary >= Rect.left && x_bottom_boundary <= Rect.right)
			{
				ball.ReboundY();
				ball.displaceY(Rect.bottom - ball_Rect.top);
				ball.displaceX(x_bottom_boundary - ball_centre.x);
			}
		return true;
    }
//collision not detected return false
	return false;
}

