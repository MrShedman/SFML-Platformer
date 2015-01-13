#pragma once

#include <Sprite.h>
#include <SpriteCore.h>
#include <Animation.h>
#include <BiDirectionX.h>
#include <BiDirectionY.h>
#include <Utility.h>

#include <memory>

#include <ResourceIdentifiers.hpp>

class SpriteState
{
public:
	virtual ~SpriteState() {}

	virtual void OnCtrlDirPress(BiDirectionX d) {}
	virtual void OnCtrlDirRelease(BiDirectionX d) {}

	virtual void OnCtrlJumpPress() {}
	virtual void OnCtrlJumpRelease() {}

	virtual void OnUpdate(sf::Time dt) { }

	virtual void OnCollision(const CollisionRectF &rect) {}
	virtual void OnFreeFall() {}

	virtual void OnCtrlClimbPress(BiDirectionY d) {};
	virtual void OnCtrlClimbRelease(BiDirectionY d) {};

	void applyDamage(int amount)
	{
		core.health -= amount;

		clamp(core.health, 0, 20);

		core.sounds->play(SoundEffect::PlayerDeath);
	}

	float getDirection()
	{
		return core.xDirection.transform(1.f);
	}

	Animation& getAnimation()
	{
		return *animation;
	}

	int ID;

protected:

	SpriteState(SpriteCore& core) : core(core) {}

	void transition(SpriteState* state)
	{
		core.state.reset(state);
	}

	Animation *animation;
	SpriteCore &core;
};