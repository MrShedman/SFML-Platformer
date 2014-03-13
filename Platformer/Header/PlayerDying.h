#pragma once

#include "SpriteState.h"

class PlayerDying : public SpriteState
{
public:
	PlayerDying(SpriteCore& core)
		:
		SpriteState(core),
		say(0.8f),
		maxsy(8.f),
		maxsx(10.f),
		sdx(0.95f),
		frameLimit(0)
	{
		core.vy = -10.f;
		core.vx = randomize(-maxsx, maxsx);
		if (core.vx > 0.f)
		{
			core.dir.SetRight();
		}
		else
		{
			core.dir.SetLeft();
		}
		core.currentSeq = core.seqs[5];
		core.currentSeq->reset();
		core.currentSeq->advanceFrame(core.dir);
		core.currentSeq->setPosition(core.x, core.y);

		ID = 5;
	}
	virtual void OnUpdate(sf::Time dt); 

protected:

	int frameLimit;

	const float sdx;
	const float maxsx;
	const float say;
	const float maxsy;
};