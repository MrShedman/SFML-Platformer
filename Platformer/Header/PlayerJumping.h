#pragma once

#include <SpriteState.h>

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
			animation = &core.mAnimationFactory.get(Animations::Jumping);
			core.sounds->play(SoundEffect::PlayerJump);
		}
		else
		{
			animation = &core.mAnimationFactory.get(Animations::Falling);
		}

		animation->reset();
		animation->setXDirection(core.xDirection);
		animation->setPosition(core.x, core.y);

		ID = 3;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirectionX d);
	virtual void OnCtrlDirRelease(BiDirectionX d);
	virtual void OnCtrlClimbPress(BiDirectionY d);
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