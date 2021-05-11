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

void Ball::Colloides_with_Wall(const Rectf & Wall)
{
	Rectf container= get_Container();
	if (container.right > Wall.right)
	{
		centre.x -= container.right - Wall.right;
		ReboundX();
	}
	if (container.left < Wall.left)
	{
		centre.x +=  Wall.left - container.left;
		ReboundX();
	}
	if (container.top < Wall.top)
	{
		centre.y += Wall.top - container.top;
		ReboundY();
	}
	if (container.bottom > Wall.bottom)
	{
		centre.y -= container.bottom - Wall.bottom;
		ReboundY();
	}

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
