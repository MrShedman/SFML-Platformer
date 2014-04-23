#include <PlayerClimbing.h>
#include <PlayerRunning.h>
#include <PlayerStanding.h>
#include <PlayerJumping.h>
#include <PlayerDying.h>

#include <algorithm>

void PlayerClimbing::OnUpdate(sf::Time dt)
{
	core.vy += core.yDirection.transform(say);
	clamp(core.vy, -maxsy, maxsy);

	core.y += core.vy;	

	if (isMoving)
	{
		core.vx += core.xDirection.transform(sax);
		clamp(core.vx, -maxsx, maxsx);
	}
	else
	{
		core.vx *= sdx;
	}

	core.x += core.vx;
	core.lastPlatformHeight = static_cast<int>(core.y);

	animation->setXDirection(core.xDirection);
	animation->update();
	animation->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		transition(new PlayerDying(core));
	}
	else if (!core.canClimb)
	{
		transition(new PlayerJumping(core, isMoving, true));
	}
}

void PlayerClimbing::OnCtrlDirPress(BiDirectionX d)
{
	core.xDirection = d;
	isMoving = true;
}

void PlayerClimbing::OnCtrlDirRelease(BiDirectionX d)
{
	if (core.xDirection == d)
	{
		isMoving = false;
	}
}

void PlayerClimbing::OnCtrlClimbPress(BiDirectionY d)
{
	core.yDirection = d;
}

void PlayerClimbing::OnCtrlClimbRelease(BiDirectionY d)
{
	if (d.IsUp())
	{
		core.yDirection.SetDown();
	}
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