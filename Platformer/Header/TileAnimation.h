#pragma once

#include <vector>
#include <Rect.h>
#include <SFML/Graphics.hpp>

class TileAnimation
{
public:
	TileAnimation()
	{}

	TileAnimation(sf::Texture &texture, int nFrames, int nHoldFrames, int nRow, int nColumn, bool cyclic) 
	: 
	texture(&texture),
	nFrames(nFrames),
	nHoldFrames(nHoldFrames),
	cyclic(cyclic)
	{
		const int width = 16;
		const int height = 16;

		int count = 0;

		for (int r = 0, dy = 0; r < nRow; ++r, dy += height)
		{
			for (int c = 0, dx = 0; c < nColumn; ++c, dx += width)
			{
				if (count++ < nFrames)
				{
					RectF rect(static_cast<float>(dy),
						static_cast<float>(dy + height),
						static_cast<float>(dx),
						static_cast<float>(dx + width));

					sequence.push_back(rect);
				}
			}
		}
		reset();
	}

	void update()
	{
		curHoldCount++;

		if (curHoldCount >= nHoldFrames)
		{
			cyclic ? updateCyclic() : updateNormal();

			curHoldCount = 0;
		}
	}

	void reset()
	{
		index = 0;
		curHoldCount = 0;
	}

	sf::Texture &getTexture() const
	{
		return *texture;
	}

	RectF getTextureRect() const
	{
		return sequence[index];
	}

private:

	void updateCyclic()
	{
		if (forward)
		{
			if (++index >= nFrames - 1)
			{
				forward = false;
			}
		}
		else
		{
			if (--index <= 0)
			{
				forward = true;
			}
		}
	}

	void updateNormal()
	{
		index++;
		index %= nFrames;
	}

	bool forward;

	bool cyclic;

	int nHoldFrames;
	int nFrames;
	int index;
	int curHoldCount;

	sf::Texture *texture;
	std::vector<RectF> sequence;
};