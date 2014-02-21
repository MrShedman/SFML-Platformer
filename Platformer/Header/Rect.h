#pragma once

template <class T>
class Rect
{
public:
	Rect()
		:
	top(0),
	bottom(0),
	left(0),
	right(0)
	{}

	Rect(T top, T bottom, T left, T right)
		:
	top(top),
	bottom(bottom),
	left(left),
	right(right)
		{}

	Rect(const Rect &rhs)
		:
	top(rhs.top),
	bottom(rhs.bottom),
	left(rhs.left),
	right(rhs.right)
	{}
	void translate(T dx, T dy)
	{
		top += dy;
		bottom += dy;
		left += dx;
		right += dx;
	}
	
public:
	T top;
	T bottom;
	T left;
	T right;
};

typedef Rect<float> RectF;
typedef Rect<int> RectI;