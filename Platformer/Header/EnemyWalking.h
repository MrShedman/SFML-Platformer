#pragma once

#include <SpriteState.h>

class EnemyWalking : public SpriteState
{
public:
	EnemyWalking(SpriteCore& core)
		:
		SpriteState(core),
		sax(0.05f),
		maxsx(1.2f)
	{
		animation = &core.mAnimationFactory.get(Animations::EnemyWalking);
		animation->reset();
		animation->setXDirection(core.xDirection);
		animation->setPosition(core.x, core.y);

		ID = 2;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCollision(const CollisionRectF &rect);
	virtual void OnFreeFall();

protected:
	const float sax;
	const float maxsx;
};