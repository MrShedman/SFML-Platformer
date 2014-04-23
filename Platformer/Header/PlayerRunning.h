#pragma once

#include <SpriteState.h>

class PlayerRunning : public SpriteState
{
public:
	PlayerRunning( SpriteCore& core )
		:
	SpriteState(core),
	sax(0.6f),
	maxsx(7.2f)
	{
		animation = &core.mAnimationFactory.get(Animations::Running);
		animation->reset();
		animation->setXDirection(core.xDirection);
		animation->setPosition(core.x, core.y);

		ID = 2;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirectionX d);
	virtual void OnCtrlDirRelease(BiDirectionX d);
	virtual void OnCtrlClimbPress(BiDirectionY d);
	virtual void OnCtrlJumpPress();
	virtual void OnCollision(const CollisionRectF &rect);
	virtual void OnFreeFall();

protected:
	const float sax;
	const float maxsx;
};