#pragma once

#include "SpriteState.h"

class PlayerRunning : public SpriteState
{
public:
	PlayerRunning( SpriteCore& core )
		:
	SpriteState(core),
	sax(0.6f),
	maxsx(7.2f)
	{
		core.currentSeq = core.seqs[ 1 ];
		core.currentSeq->reset();
		core.currentSeq->advanceFrame(core.dir);
		core.currentSeq->setPosition(core.x, core.y);

		ID = 2;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlDirRelease(BiDirection d);
	virtual void OnCtrlClimbPress(ClimbDirection d);
	virtual void OnCtrlJumpPress();
	virtual void OnCollision(const CollisionRectF &rect);
	virtual void OnFreeFall();

protected:
	const float sax;
	const float maxsx;
};