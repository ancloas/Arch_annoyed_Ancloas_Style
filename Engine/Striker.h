#pragma once
#include "Rectf.h"
#include "Ball.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"

class Striker {

public:
	Striker(const Vec2 &StartPosition, float width, float height,Vec2 velocity, Color c);
	bool hit_ball(Ball &b);
	void touched_wall(Rectf & wall);
	void update(Keyboard &Kbd, float dt);
	void Draw(Graphics &gfx);
private:
	Rectf container;
	Vec2 velocity;
	Color color;
};