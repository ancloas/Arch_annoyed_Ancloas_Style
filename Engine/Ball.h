#pragma once
#include"Vec2.h"
#include "Rectf.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(const Vec2 & centre, const Vec2& velocity);
	void Update(float dt);
	void Colloides_with_Wall(const Rectf& Wall);
	void ReboundX();
	void ReboundY();
	void Draw(Graphics &gfx);
	Rectf get_Container() const;
private:
	Vec2 centre;
	Vec2 velocity;
	const float radius=7;
};