#pragma once

class ClimbDirection
{
public:
	ClimbDirection(const ClimbDirection& d)
	{
		dir = d.dir;
	}
	ClimbDirection()
	{
		dir = Invalid;
	}
	static ClimbDirection MakeDown()
	{
		ClimbDirection d;
		d.SetDown();
		return d;
	}
	static ClimbDirection MakeUp()
	{
		ClimbDirection d;
		d.SetUp();
		return d;
	}

	void SetUp()
	{
		dir = Up;
	}
	void SetDown()
	{
		dir = Down;
	}
	bool IsUp() const
	{
		return dir == Up;
	}
	bool IsDown() const
	{
		return dir == Down;
	}
	bool IsInvalid() const
	{
		return dir == Invalid;
	}
	bool operator ==(const ClimbDirection& rhs) const
	{
		return dir == rhs.dir;
	}
	bool operator !=(const ClimbDirection& rhs) const
	{
		return dir != rhs.dir;
	}
	ClimbDirection& operator =(const ClimbDirection& rhs)
	{
		dir = rhs.dir;
		return *this;
	}
	ClimbDirection GetOpposite() const
	{
		ClimbDirection o;
		if (dir == Up)
		{
			o.SetDown();
		}
		else if (dir == Down)
		{
			o.SetUp();
		}
		return o;
	}
	void Reverse()
	{
		if (dir == Up)
		{
			SetDown();
		}
		else if (dir == Down)
		{
			SetUp();
		}
	}

	float transform(float value) const
	{
		if (dir == Up)
		{
			return value * -1.0f;
		}
		else if (dir == Down)
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
		Up,
		Down,
		Invalid
	} dir;
};