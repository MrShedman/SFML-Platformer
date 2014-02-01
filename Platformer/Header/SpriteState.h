#pragma once

#include <list>

#include "Sprite.h"
#include "SpriteCore.h"
#include <BiDirection.h>

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

	virtual void OnUpdate() {}

	virtual void OnCollision(const RectF &rect) {}
	virtual void OnFreeFall() {}

	int ID;

protected:

	void transition(SpriteState *state)
	{
		core.state = state;
		delete this;
	}

	SpriteCore& core;
};