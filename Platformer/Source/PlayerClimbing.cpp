#include <PlayerClimbing.h>
#include "PlayerRunning.h"
#include "PlayerStanding.h"
#include <PlayerJumping.h>
#include <PlayerDying.h>

#include <algorithm>

void PlayerClimbing::OnUpdate(sf::Time dt)
{
	if (!isFrozen)
	{
		core.vy += core.climbdir.transform(say);
		clamp(core.vy, -maxsy, maxsy);

		core.y += core.vy;
	}

	if (isMoving)
	{
		core.vx += core.dir.transform(sax);
		clamp(core.vx, -maxsx, maxsx);
	}
	else
	{
		core.vx *= sdx;
	}

	core.x += core.vx;
	core.lastPlatformHeight = core.y;

	if (!isFrozen || isMoving)
	{
		core.currentSeq->advanceFrame(core.dir);
		core.currentSeq->setPosition(core.x, core.y);
	}

	if (!core.canClimb)
	{
		transition(new PlayerJumping(core, isMoving, true));
	}

	if (core.health <= 0)
	{
		transition(new PlayerDying(core));
	}
}

void PlayerClimbing::OnCtrlDirPress(BiDirection d)
{
	core.dir = d;
	isMoving = true;
}

void PlayerClimbing::OnCtrlDirRelease(BiDirection d)
{
	if (core.dir == d)
	{
		isMoving = false;
	}
}

void PlayerClimbing::OnCtrlClimbPress(ClimbDirection d)
{
	core.climbdir = d;
}

void PlayerClimbing::OnCtrlClimbRelease(ClimbDirection d)
{
	if (d.IsUp())
	{
		core.climbdir.SetDown();
	}
}

void PlayerClimbing::OnCtrlClimbFreezePress()
{
	isFrozen = true;
}

void PlayerClimbing::OnCtrlClimbFreezeRelease()
{
	isFrozen = false;
}

void PlayerClimbing::OnCollision(const CollisionRectF &rect)
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