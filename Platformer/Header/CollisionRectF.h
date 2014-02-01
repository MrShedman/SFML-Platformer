#pragma once

#include <RectF.h>

class CollisionRectF : public RectF
{
public:
	CollisionRectF(){}
	CollisionRectF(const CollisionRectF &rhs)
		:
	RectF(rhs.top, rhs.bottom, rhs.left, rhs.right),
	vx(rhs.vx),
	vy(rhs.vy)
	{}
	CollisionRectF(float top, float bottom, float left, float right, float vx, float vy)
		:
	RectF(top, bottom, left, right),
	vx(vx),
	vy(vy)
	{}

	CollisionRectF(const RectF &rhs, float vx = 0.f, float vy = 0.f)
		:
	RectF(rhs.top, rhs.bottom, rhs.left, rhs.right),
	vx(vx),
	vy(vy)
	{}

public:
	float vx;
	float vy;
};