#include "PlayerRunning.h"
#include "PlayerStanding.h"
#include <PlayerJumping.h>
#include <PlayerClimbing.h>
#include <PlayerDying.h>

void PlayerRunning::OnUpdate(sf::Time dt)
{
	core.vx += core.dir.transform(sax);
	clamp(core.vx, -maxsx, maxsx);

	core.x += core.vx;

	core.currentSeq->advanceFrame(core.dir);
	core.currentSeq->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		transition(new PlayerDying(core));
	}
}

void PlayerRunning::OnCtrlDirPress(BiDirection d)
{
	core.dir = d;
}

void PlayerRunning::OnCtrlDirRelease(BiDirection d)
{
	if (core.dir == d)
	{
		transition(new PlayerStanding(core));
	}
}

void PlayerRunning::OnCtrlJumpPress()
{
	transition(new PlayerJumping(core, true));
}

void PlayerRunning::OnCtrlClimbPress(ClimbDirection d)
{
	if (core.canClimb)
	{
		core.climbdir = d;
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