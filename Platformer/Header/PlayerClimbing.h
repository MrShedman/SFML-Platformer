#pragma once

#include <SpriteState.h>

class PlayerClimbing : public SpriteState
{
public:
	PlayerClimbing(SpriteCore& core, bool isMoving = false)
		:
		SpriteState(core),
		say(0.8f),
		maxsy(5.f),
		sax(0.2f),
		maxsx(3.3f),
		sdx(0.8f),
		isMoving(isMoving)
	{
		animation = &core.mAnimationFactory.get(Animations::Climbing);
		animation->reset();
		animation->setXDirection(core.xDirection);
		animation->setPosition(core.x, core.y);

		ID = 4;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirectionX d);
	virtual void OnCtrlDirRelease(BiDirectionX d);
	virtual void OnCtrlClimbPress(BiDirectionY d);
	virtual void OnCtrlClimbRelease(BiDirectionY d);

	virtual void OnCollision(const CollisionRectF &rect);


protected:

	bool isMoving;

	const float sdx;
	const float sax;
	const float maxsx;
	const float say;
	const float maxsy;
};