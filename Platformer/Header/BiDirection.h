#pragma once

class BiDirection
{
public:
	BiDirection(const BiDirection& d)
	{
		dir = d.dir;
	}
	BiDirection()
	{
		dir = Invalid;
	}
	static BiDirection MakeRight()
	{
		BiDirection d;
		d.SetRight();
		return d;
	}
	static BiDirection MakeLeft()
	{
		BiDirection d;
		d.SetLeft();
		return d;
	}

	void SetLeft()
	{
		dir = Left;
	}
	void SetRight()
	{
		dir = Right;
	}
	bool IsLeft() const
	{
		return dir == Left;
	}
	bool IsRight() const
	{
		return dir == Right;
	}
	bool IsInvalid() const
	{
		return dir == Invalid;
	}
	bool operator ==(const BiDirection& rhs) const
	{
		return dir == rhs.dir;
	}
	bool operator !=(const BiDirection& rhs) const
	{
		return dir != rhs.dir;
	}
	BiDirection& operator =(const BiDirection& rhs)
	{
		dir = rhs.dir;
		return *this;
	}
	BiDirection GetOpposite() const
	{
		BiDirection o;
		if (dir == Left)
		{
			o.SetRight();
		}
		else if (dir == Right)
		{
			o.SetLeft();
		}
		return o;
	}
	void Reverse()
	{
		if (dir == Left)
		{
			SetRight();
		}
		else if (dir == Right)
		{
			SetLeft();
		}
	}

	float transform(float value) const
	{
		if (dir == Left)
		{
			return value * -1.0f;
		}
		else if (dir == Right)
		{
			return value;
		}
		else
		{
			return 0.f;
		}
	}

private:
	enum BiDir
	{
		Left,
		Invalid,
		Right
	} dir;
};