#pragma once

#include <SpriteSequence.h>
#include <CollisionRectF.h>
#include <ClimbDirection.h>

class SpriteCore
{
public:

	float x;
	float y;
	float vx;
	float vy;
	SpriteSequence* currentSeq;
	SpriteSequence** seqs;
	class SpriteState* state;
	BiDirection dir;
	ClimbDirection climbdir;

	CollisionRectF getCRect() const
	{
		CollisionRectF cRect(rect, vx, vy);
		cRect.translate(x, y);
		return cRect;
	}

	bool canClimb;
	int health;
	int lastPlatformHeight;

	RectF rect;
};