#pragma once

#include <SpriteState.h>

class PlayerStanding : public SpriteState
{
public:
	PlayerStanding( SpriteCore& core )
		:
	SpriteState(core),
	sdx(0.8f)
	{
		animation = &core.mAnimationFactory.get(Animations::Standing);
		animation->reset();
		animation->update();
		animation->setPosition(core.x, core.y);

		ID = 1;
	}
	virtual void OnUpdate(sf::Time dt);
	virtual void OnCtrlDirPress(BiDirectionX d);
	virtual void OnCtrlJumpPress();
	virtual void OnCtrlClimbPress(BiDirectionY d);
	virtual void OnCollision(const CollisionRectF &rect);
	virtual void OnFreeFall();

protected:
	const float sdx;
};