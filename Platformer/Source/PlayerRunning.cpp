#include <PlayerRunning.h>
#include <PlayerStanding.h>
#include <PlayerJumping.h>
#include <PlayerClimbing.h>
#include <PlayerDying.h>

void PlayerRunning::OnUpdate(sf::Time dt)
{
	core.vx += core.xDirection.transform(sax);
	clamp(core.vx, -maxsx, maxsx);

	core.x += core.vx;

	animation->setXDirection(core.xDirection);
	animation->update();
	animation->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		transition(new PlayerDying(core));
	}
}

void PlayerRunning::OnCtrlDirPress(BiDirectionX d)
{
	core.xDirection = d;
}

void PlayerRunning::OnCtrlDirRelease(BiDirectionX d)
{
	if (core.xDirection == d)
	{
		transition(new PlayerStanding(core));
	}
}

void PlayerRunning::OnCtrlJumpPress()
{
	transition(new PlayerJumping(core, true));
}

void PlayerRunning::OnCtrlClimbPress(BiDirectionY d)
{
	if (core.canClimb)
	{
		core.yDirection = d;
		transition(new PlayerClimbing(core, true));
	}
}

void PlayerRunning::OnCollision(const CollisionRectF &rect)
{
	if (core.vx > 0.f)
	{
		core.x -= core.getCRect().right - rect.left;
		core.vx = 0.0f;
	}
	else
	{
		core.x += rect.right - core.getCRect().left;
		core.vx = 0.0f;
	}
}

void PlayerRunning::OnFreeFall()
{
	transition(new PlayerJumping(core, true, true));
}