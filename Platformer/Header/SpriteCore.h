#pragma once

#include <SpriteSequence.h>
#include <CollisionRectF.h>

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

	CollisionRectF getCRect() const
	{
		CollisionRectF cRect(rect, vx, vy);
		cRect.translate(x, y);
		return cRect;
	}

	RectF rect;
};