#pragma once

class BiDirectionY
{
public:
	BiDirectionY(const BiDirectionY& d)
	{
		dir = d.dir;
	}
	BiDirectionY()
	{
		dir = Invalid;
	}
	static BiDirectionY MakeDown()
	{
		BiDirectionY d;
		d.SetDown();
		return d;
	}
	static BiDirectionY MakeUp()
	{
		BiDirectionY d;
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
	bool operator ==(const BiDirectionY& rhs) const
	{
		return dir == rhs.dir;
	}
	bool operator !=(const BiDirectionY& rhs) const
	{
		return dir != rhs.dir;
	}
	BiDirectionY& operator =(const BiDirectionY& rhs)
	{
		dir = rhs.dir;
		return *this;
	}
	BiDirectionY GetOpposite() const
	{
		BiDirectionY o;
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