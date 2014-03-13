#pragma once

#include "SpriteState.h"

class PlayerJumping : public SpriteState
{
public:
	PlayerJumping(SpriteCore& core, bool isMoving, bool isFalling = false)
		:
		SpriteState(core),
		isMoving(isMoving),
		ay(0.72f),
		sax(0.48f),
		sdx(0.97f),
		sdy(0.9f),
		maxsx(9.f),
		jumpImpulse(-18),
		isBoosting(true),
		doubleJumped(false)
	{
		if (!isFalling && !doubleJumped)
		{
			core.vy = jumpImpulse;
			core.currentSeq = core.seqs[2];
		}
		else
		{
			core.currentSeq = core.seqs[3];
		}
		core.currentSeq->reset();
		core.currentSeq->advanceFrame(core.dir);
		core.currentSeq->setPosition(core.x, core.y);

		ID = 3;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlDirRelease(BiDirection d);
	virtual void OnCtrlClimbPress(ClimbDirection d);
	virtual void OnCtrlJumpPress();
	virtual void OnCtrlJumpRelease();
	virtual void OnCollision(const CollisionRectF &rect);


protected:

	const float jumpImpulse;
	const float sax;
	const float sdx;
	const float sdy;
	const float ay;
	const float maxsx;
	bool isMoving;
	bool isBoosting;
	bool doubleJumped;
};