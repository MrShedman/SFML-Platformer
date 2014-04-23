#include <PlayerStanding.h>
#include <PlayerRunning.h>
#include <PlayerJumping.h>
#include <PlayerClimbing.h>
#include <PlayerDying.h>

void PlayerStanding::OnUpdate(sf::Time dt)
{
	core.vx *= sdx;
	core.x += core.vx;

	animation->setXDirection(core.xDirection);
	animation->update();
	animation->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		transition(new PlayerDying(core));
	}
}

void PlayerStanding::OnCtrlDirPress(BiDirectionX d)
{
	core.xDirection = d;
	transition(new PlayerRunning(core));
}

void PlayerStanding::OnCtrlJumpPress()
{
	transition(new PlayerJumping(core, false));
}

void PlayerStanding::OnCtrlClimbPress(BiDirectionY d)
{
	if (core.canClimb)
	{
		core.yDirection = d;
		transition(new PlayerClimbing(core));
	}
}

void PlayerStanding::OnCollision(const CollisionRectF &rect)
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

void PlayerStanding::OnFreeFall()
{
	transition(new PlayerJumping(core, false, true));
}