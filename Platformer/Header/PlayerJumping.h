#pragma once

#include "SpriteState.h"

class PlayerJumping : public SpriteState
{
public:
	PlayerJumping(SpriteCore& core, bool isMoving, bool hasJumped = true)
		:
		SpriteState(core),
		isMoving(isMoving),
		ay(0.6f),
		sax(0.4f),
		sdx(0.97f),
		sdy(0.9f),
		maxsx(7.5f),
		isBoosting(true)
	{
		if (hasJumped)
		{
			core.vy = -15.0f;
			core.currentSeq = core.seqs[2];
		}
		else
		{
			core.currentSeq = core.seqs[3];
		}
		core.currentSeq->reset();

		ID = 3;
	}
	virtual void OnUpdate();
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlDirRelease(BiDirection d);
	virtual void OnCtrlJumpPress();
	virtual void OnCtrlJumpRelease();
	virtual void OnCollision(const RectF &rect);


protected:

	const float sax;
	const float sdx;
	const float sdy;
	const float ay;
	const float maxsx;
	bool isMoving;
	bool isBoosting;
};