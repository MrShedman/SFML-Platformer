#pragma once

#include <SpriteState.h>

class EnemyFalling : public SpriteState
{
public:
	EnemyFalling(SpriteCore& core)
		:
		SpriteState(core),
		ay(0.32f),
		say(11.f),
		sdx(0.97f),
		sdy(0.9f),
		maxsx(9.f)
	{
		animation = &core.mAnimationFactory.get(Animations::EnemyWalking);
	
		animation->reset();
		animation->setXDirection(core.xDirection);
		animation->setPosition(core.x, core.y);

		ID = 3;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCollision(const CollisionRectF &rect);


protected:

	const float say;
	const float sdx;
	const float sdy;
	const float ay;
	const float maxsx;
};