#pragma once
#include"Vec2.h"
#include "Rectf.h"
#include "Graphics.h"

class Ball
{
public:
	Ball(const Vec2 & centre, const Vec2& velocity);
	void Update(float dt);
	bool Colloides_with_Wall(const Rectf& Wall);
	void ReboundX();
	void ReboundY();
	void Draw(Graphics &gfx);
	Rectf get_Container() const;
	const Vec2& Peek_Velocity() const;
	void Suspend_Ball(const Vec2& Position);
	const bool & Did_Hit_Floor();
	const Vec2& Peek_Centre() const;
	void displaceX(const float & dx);
	void displaceY(const float & dy);
	void Accelarate(const Vec2& vel);
	
private:
	Vec2 centre;
	Vec2 velocity;
	const float radius=7;
	bool hit_floor = false;
};