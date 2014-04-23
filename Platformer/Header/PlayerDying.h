#pragma once

#include <SpriteState.h>

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
			core.xDirection.SetRight();
		}
		else
		{
			core.xDirection.SetLeft();
		}

		animation = &core.mAnimationFactory.get(Animations::Dying);
		animation->reset();
		animation->setXDirection(core.xDirection);
		animation->setPosition(core.x, core.y);

		core.sounds->play(SoundEffect::PlayerDeath);

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