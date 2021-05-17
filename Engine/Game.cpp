/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																																															  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <Windows.h>
#include "Screen.h"


Game::Game(MainWindow & wnd)
:
wnd(wnd),
gfx(wnd),
Wall(50, Graphics::ScreenWidth - 50, 50, Graphics::ScreenHeight - 50),
Brick_wall_start(Wall.left, Wall.top + 20),
ball(Vec2((Wall.left + Wall.right) / 2, (Wall.top + Wall.bottom) / 2), Vec2(300.0f, 300.0f)),
striker(Vec2((Wall.left + Wall.right) / 2, Wall.bottom - 20.0f), 150.0f, 20.0f, Vec2(400.0f, 0.0f), Colors::Red),
brick_break(L"Sounds\\arkbrick.wav"),
striker_hit(L"Sounds\\arkpad.wav"),
wall_strike(L"Sounds\\arkpad.wav")
{
	create_wall_of_bricks();
}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedtime;//assingning elapsedtime variable
	if (ball.Did_Hit_Floor())
	{
		ball.Accelarate(Vec2(0,300.0f));
		Sleep(5000); //put to sleep for 5 secs
		elapsedtime = ft.Mark() - 5000;  //remove the time in sleep
		Life--; // Life decrement
	}
	else {
		elapsedtime = ft.Mark();
	}
	while (elapsedtime > 0.0f)
	{
		float dt = std::min(elapsedtime, 0.0025f);
		UpdateModel(dt);
		elapsedtime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (!gamestart)
	{
		gamestart = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
	else
	{
		if (Life < 0)
			gameover = true;
		if (!gameover)
		{
			striker.Update(wnd.kbd, dt);
			ball.Update(dt);

			if (striker.Hit_Ball(ball))
			{
				striker_hit.Play();
			}
			for (Brick & b : bricks)
			{
				if (b.Colloides_With_Ball(ball))
				{
					//play sound dude
					// delete the object at position later
					brick_break.Play();
					break;
				}
			}

			if (ball.Colloides_with_Wall(Wall))
			{
				//play sound
				wall_strike.Play();
			}
			striker.Touched_Wall(Wall);//bounding striker to wall 
		}
	else
		{
		//asked to press enter to play again
			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				ball.Suspend_Ball(Wall.Get_Centre());
				ball.Accelarate(Vec2(0.0f, 300.0f));
				striker.Recentre(Wall.Get_Centre().x);
				Life = 3;
			}
	    }
    }
}

void Game::create_wall_of_bricks()
{
	
	//brick width
	
		brick_width = (Wall.right - Wall.left) / num_of_bricks_in_row;
		brick_height = ((Wall.bottom - Wall.top) * 30 / 100) / num_of_bricks_in_cols;

		for (int i = 0; i < num_of_bricks_in_cols; i++)
		{
			for (int j = 0; j < num_of_bricks_in_row; j++)
			{//push_back new brick object
				Color c;
				if (i % 2 == 0)
				{
					c = Colors::Green;
				}
				else c = Colors::Yellow;
				bricks.push_back(Brick(Brick_wall_start + Vec2(j*brick_width, i*brick_height), brick_width, brick_height, c));
			}
		}
}

void Game::ComposeFrame()
{
	if (!gamestart)
	{
		draw_title_screen(20, 20, gfx);
		return;
    }

	if (gameover)
		draw_game_over(300,300,gfx);
	ball.Draw(gfx);
	for (Brick b : bricks)
		b.Draw_with_padding(gfx);
	Wall.draw_hollow(gfx, Colors::White, 10);
	striker.Draw(gfx);
	
	//test brick
 }
