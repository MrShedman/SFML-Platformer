#include "PlayerRunning.h"
#include "PlayerStanding.h"
#include <PlayerJumping.h>

#include <algorithm>

void PlayerJumping::OnUpdate(sf::Time dt)
{
	core.vy += ay;

	if (isMoving)
	{
		core.vx += core.dir.transform(sax);
		core.vx = std::min(core.vx, maxsx);
		core.vx = std::max(core.vx, -maxsx);
	}
	else
	{
		core.vx *= sdx;
	}

	if (!isBoosting && core.vy < 0.0f)
	{
		core.vy *= sdy;
	}
	
	if (core.vy >= 0.f)
	{
		core.currentSeq = core.seqs[3];
	}

	core.x += core.vx;
	core.y += core.vy;
	
	core.currentSeq->advance(core.x, core.y, core.dir);
}

void PlayerJumping::OnCtrlDirPress(BiDirection d)
{
	core.dir = d;
	isMoving = true;
}

void PlayerJumping::OnCtrlDirRelease(BiDirection d)
{
	if (core.dir == d)
	{
		isMoving = false;
	}
}

void PlayerJumping::OnCtrlJumpPress()
{
	//DOUBLE JUMP FEATURE//

	if (core.vy < 18.f && core.vy > -10.f && !doubleJumped)
	{
		doubleJumped = true;

		core.vy = jumpImpulse;
		core.currentSeq = core.seqs[2];
		core.currentSeq->reset();
	}
}

void PlayerJumping::OnCtrlJumpRelease()
{
	isBoosting = false;
}

void PlayerJumping::OnCollision(const CollisionRectF &rect)
{
	CollisionRectF sRect = core.getCRect();

	if (core.vx > 0.f)
	{
		if (core.vy > 0.f)
		{
			float px = sRect.right - rect.left;
			float py = sRect.bottom - rect.top;

			if (core.vy * px > core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y -= py;			

				if (isMoving)
				{
					transition(new PlayerRunning(core));
				}
				else
				{
					transition(new PlayerStanding(core));
				}
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x -= px;
			}
		}
		else //core.vy > 0.f
		{
			float px = sRect.right - rect.left;
			float py = rect.bottom - sRect.top;

			if (-core.vy * px > core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y += py;
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x -= px;
			}			
		}
	}
	else // core.vx > 0.f
	{
		if (core.vy > 0.f)
		{
			float px = rect.right - sRect.left;
			float py = sRect.bottom - rect.top;

			if (core.vy * px > -core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y -= py;

				if (isMoving)
				{
					transition(new PlayerRunning(core));
				}
				else
				{
					transition(new PlayerStanding(core));
				}
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x += px;
			}
		}
		else //core.vy > 0.f
		{
			float px = rect.right - sRect.left;
			float py = rect.bottom - sRect.top;

			if (-core.vy * px > -core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y += py;
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x += px;
			}
		}
	}
}