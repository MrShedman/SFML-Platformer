#pragma once

#include <memory>

#include <Animation.h>
#include <CollisionRectF.h>
#include <BiDirectionX.h>
#include <BiDirectionY.h>
#include <AnimationFactory.h>
#include <SoundPlayer.hpp>

class SpriteState;

class SpriteCore
{
public:

	float x;
	float y;
	float vx;
	float vy;

	AnimationFactory mAnimationFactory;

	std::unique_ptr<SpriteState> state;

	BiDirectionX xDirection;
	BiDirectionY yDirection;

	CollisionRectF getCRect() const
	{
		CollisionRectF cRect(rect, vx, vy);
		cRect.translate(x, y);
		return cRect;
	}

	bool canClimb;
	int health;
	int lastPlatformHeight;
	float damage_rate;
	sf::Clock damage_clock;

	void setSoundPlayer(SoundPlayer &player)
	{
		sounds = &player;
	}

	SoundPlayer *sounds;

	RectF rect;
};