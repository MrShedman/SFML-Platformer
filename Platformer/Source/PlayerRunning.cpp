#include "PlayerRunning.h"
#include "PlayerStanding.h"
#include <PlayerJumping.h>

void PlayerRunning::OnUpdate()
{
	core.vx += core.dir.transform(sax);
	core.vx = std::min(core.vx, maxsx);
	core.vx = std::max(core.vx, -maxsx);

	core.x += core.vx;

	core.currentSeq->advance(core.x, core.y, core.dir);
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