#pragma once

#include "Sprite.h"
#include "SpriteCore.h"
#include <BiDirection.h>
#include <ClimbDirection.h>
#include <Utility.h>

class SpriteState
{
public:
	SpriteState( SpriteCore& core )
		:
	core( core )
	{}

	virtual ~SpriteState() {}

	virtual void OnCtrlDirPress( BiDirection d ) {}
	virtual void OnCtrlDirRelease( BiDirection d ) {}

	virtual void OnCtrlJumpPress() {}
	virtual void OnCtrlJumpRelease() {}

	virtual void OnUpdate(sf::Time dt) {}

	virtual void OnCollision(const CollisionRectF &rect) {}
	virtual void OnFreeFall() {}

	virtual void OnCtrlClimbPress(ClimbDirection d) {};
	virtual void OnCtrlClimbRelease(ClimbDirection d) {};
	virtual void OnCtrlClimbFreezePress(){};
	virtual void OnCtrlClimbFreezeRelease(){};

	void applyDamage(int amount)
	{
		core.health -= amount;

		clamp(core.health, 0, 20);
	}

	int ID;

protected:

	void transition(SpriteState *state)
	{
		core.state = state;
		delete this;
	}

	SpriteCore& core;
};