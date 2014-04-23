#pragma once

class BiDirectionX
{
public:
	BiDirectionX(const BiDirectionX& d)
	{
		dir = d.dir;
	}
	BiDirectionX()
	{
		dir = Invalid;
	}
	static BiDirectionX MakeRight()
	{
		BiDirectionX d;
		d.SetRight();
		return d;
	}
	static BiDirectionX MakeLeft()
	{
		BiDirectionX d;
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
	bool operator ==(const BiDirectionX& rhs) const
	{
		return dir == rhs.dir;
	}
	bool operator !=(const BiDirectionX& rhs) const
	{
		return dir != rhs.dir;
	}
	BiDirectionX& operator =(const BiDirectionX& rhs)
	{
		dir = rhs.dir;
		return *this;
	}
	BiDirectionX GetOpposite() const
	{
		BiDirectionX o;
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