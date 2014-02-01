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

		ID = 1;
	}
	virtual void OnUpdate();
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlJumpPress();
	virtual void OnCollision(const RectF &rect);
	virtual void OnFreeFall();

protected:
	const float sdx;
};