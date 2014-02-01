#include "PlayerStanding.h"
#include "PlayerRunning.h"
#include <PlayerJumping.h>

void PlayerStanding::OnUpdate()
{
	core.vx *= sdx;

	core.x += core.vx;

	core.currentSeq->advance(core.x, core.y, core.dir);
}

void PlayerStanding::OnCtrlDirPress(BiDirection d)
{
	core.dir = d;
	transition(new PlayerRunning(core));
}

void PlayerStanding::OnCtrlJumpPress()
{
	transition(new PlayerJumping(core, false));
}

void PlayerStanding::OnCollision(const RectF &rect)
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
	transition(new PlayerJumping(core, false, false));
}