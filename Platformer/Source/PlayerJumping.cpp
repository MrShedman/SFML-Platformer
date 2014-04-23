#include <PlayerRunning.h>
#include <PlayerStanding.h>
#include <PlayerJumping.h>
#include <PlayerClimbing.h>
#include <PlayerDying.h>

#include <algorithm>

void PlayerJumping::OnUpdate(sf::Time dt)
{
	core.vy += ay;

	if (isMoving)
	{
		core.vx += core.xDirection.transform(sax);
		clamp(core.vx, -maxsx, maxsx);
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
		animation = &core.mAnimationFactory.get(Animations::Falling);
	}

	core.x += core.vx;
	core.y += core.vy;

	animation->setXDirection(core.xDirection);
	animation->update();
	animation->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		transition(new PlayerDying(core));
	}
	else if (core.canClimb && core.vy > 0.0f)
	{
		core.yDirection.SetDown();
		transition(new PlayerClimbing(core, isMoving));
	}
}

void PlayerJumping::OnCtrlDirPress(BiDirectionX d)
{
	core.xDirection = d;
	isMoving = true;
}

void PlayerJumping::OnCtrlDirRelease(BiDirectionX d)
{
	if (core.xDirection == d)
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

		animation = &core.mAnimationFactory.get(Animations::Jumping);
		animation->reset();

		core.sounds->play(SoundEffect::PlayerJump);
	}
}

void PlayerJumping::OnCtrlJumpRelease()
{
	isBoosting = false;
}

void PlayerJumping::OnCtrlClimbPress(BiDirectionY d)
{
	if (core.canClimb)
	{
		core.yDirection = d;
		transition(new PlayerClimbing(core, isMoving));
	}
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