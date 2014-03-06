#pragma once

#include "SpriteState.h"

class PlayerClimbing : public SpriteState
{
public:
	PlayerClimbing(SpriteCore& core, bool isMoving = false)
		:
		SpriteState(core),
		say(0.5f),
		maxsy(5.f),
		sax(0.2),
		maxsx(3.3),
		sdx(0.8f),
		isMoving(isMoving),
		isFrozen(false)
	{
		core.currentSeq = core.seqs[4];
		core.currentSeq->reset();
		core.currentSeq->advance(core.x, core.y, core.dir);

		ID = 4;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirection d);
	virtual void OnCtrlDirRelease(BiDirection d);
	virtual void OnCtrlClimbPress(ClimbDirection d);
	virtual void OnCtrlClimbRelease(ClimbDirection d);
	virtual void OnCtrlClimbFreezePress();
	virtual void OnCtrlClimbFreezeRelease();

	virtual void OnCollision(const CollisionRectF &rect);


protected:

	bool isMoving;
	bool isFrozen;

	const float sdx;
	const float sax;
	const float maxsx;
	const float say;
	const float maxsy;
};