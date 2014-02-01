#pragma once

#include "SpriteState.h"

class PlayerRunning : public SpriteState
{
public:
	PlayerRunning( SpriteCore& core )
		:
	SpriteState(core),
	sax(0.5f),
	maxsx(6.0f)
	{
		core.currentSeq = core.seqs[ 1 ];
		core.currentSeq->reset();

		ID = 2;
	}
	virtual void OnUpdate();
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlDirRelease(BiDirection d);
	virtual void OnCtrlJumpPress();
	virtual void OnCollision(const RectF &rect);
	virtual void OnFreeFall();

protected:
	const float sax;
	const float maxsx;
};