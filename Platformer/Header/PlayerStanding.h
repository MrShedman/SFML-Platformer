#pragma once

#include "SpriteState.h"

class PlayerStanding : public SpriteState
{
public:
	PlayerStanding( SpriteCore& core )
		:
	SpriteState(core),
	sdx(0.8f)
	{
		core.currentSeq = core.seqs[ 0 ];
		core.currentSeq->reset();
		core.currentSeq->advanceFrame(core.dir);
		core.currentSeq->setPosition(core.x, core.y);

		ID = 1;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlJumpPress();
	virtual void OnCtrlClimbPress(ClimbDirection d);
	virtual void OnCollision(const CollisionRectF &rect);
	virtual void OnFreeFall();

protected:
	const float sdx;
};