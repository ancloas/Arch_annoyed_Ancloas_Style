#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2 & centre, const Vec2& velocity )
	:
	centre(centre),
	velocity(velocity)
{
}

void Ball::Update(float dt)
{
	centre += velocity * dt;
}

bool Ball::Colloides_with_Wall(const Rectf & Wall)
{
	bool colloide = false;
	Rectf container= get_Container();
	if (container.right > Wall.right)
	{
		centre.x -= container.right - Wall.right;
		ReboundX();
		colloide= true;

	}
	if (container.left <= Wall.left)
	{
		centre.x +=  Wall.left - container.left;
		ReboundX();
		colloide = true;

	}
	if (container.top <= Wall.top)
	{
		centre.y += Wall.top - container.top;
		ReboundY();
		colloide = true;
	}

	if (container.bottom >= Wall.bottom)
	{
		hit_floor = true;
		Suspend_Ball(Wall.Get_Centre());
	}
	return colloide;
}

void Ball::ReboundX()
{
	velocity.x *= -1;
}

void Ball::ReboundY()
{
	velocity.y *= -1;
}

void Ball::Draw(Graphics & gfx)
{
	SpriteCodex::DrawBall(centre, gfx);
}

Rectf Ball::get_Container() const
{
	Rectf a;
	a.Draw_from_centre(centre, radius * 2, radius * 2);
	return a;
}

const Vec2 & Ball::Peek_Centre() const
{
	return centre;
}

void Ball::displaceX(const float & dx)
{
	centre.x += dx;
}
void Ball::displaceY(const float &dy)
{
	centre.y += dy;
}

void Ball::Accelarate(const Vec2 & vel)
{
	velocity = vel;
	hit_floor = false;
}

const Vec2 & Ball::Peek_Velocity() const
{
	return velocity;
}

void Ball::Suspend_Ball(const Vec2 &Position)
{
	velocity.x = 0;
	velocity.y = 0;
	centre = Position;
}
const bool& Ball::Did_Hit_Floor()
{
	return hit_floor;
}