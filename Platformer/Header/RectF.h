#pragma once

class RectF
{
public:
	RectF()
		:
	top(0.f),
	bottom(0.f),
	left(0.f),
	right(0.f)
	{}

	RectF(float top, float bottom, float left, float right)
		:
	top(top),
	bottom(bottom),
	left(left),
	right(right)
		{}

	RectF(const RectF &rhs)
		:
	top(rhs.top),
	bottom(rhs.bottom),
	left(rhs.left),
	right(rhs.right)
	{}
	void translate(float dx, float dy)
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	
public:
	float top;
	float bottom;
	float left;
	float right;
};