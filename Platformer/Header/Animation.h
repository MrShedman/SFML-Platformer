#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include <BiDirectionX.h>

class Animation : public sf::Drawable, public sf::Transformable
{
public:
	Animation(sf::Texture &mTexture, int nFrames, int nHoldFrames, int nRow, int nColumn)
		:
		texture(mTexture),
		nFrames(nFrames),
		nHoldFrames(nHoldFrames),
		index(0),
		m_scale(0.72f)
	{
		texture.setSmooth(true);
		sprite.setTexture(texture);

		const int width = 200;
		const int height = 200;
		const int border = 10;

		int count = 0;

		for (int r = 0, dy = border; r < nRow; ++r, dy += height)
		{
			for (int c = 0, dx = border; c < nColumn; ++c, dx += width)
			{
				if (count++ < nFrames)
				{
					sequence.push_back(sf::IntRect(dx, dy, width - 2 * border, height - 2 * border));
				}
			}
		}

		sprite.setTextureRect(sequence.front());
		setOrigin(width / 2 - border, height / 2 - border);
		setScale(m_scale, m_scale);
	}

	void setXDirection(BiDirectionX d)
	{
		if (d.IsRight())
		{
			setScale(m_scale, m_scale);
		}
		else
		{
			setScale(-m_scale, m_scale);
		}
	}

	void update()
	{
		curHoldCount++;

		if (curHoldCount >= nHoldFrames)
		{
			index++;
			index %= nFrames;
			curHoldCount = 0;
		}

		sprite.setTextureRect(sequence[index]);
	}

	void reset()
	{
		index = 0;
		curHoldCount = 0;
		sprite.setTextureRect(sequence[index]);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(sprite, states);
	}

private:

	const int nHoldFrames;
	const int nFrames;
	int index;
	int curHoldCount;

	const float m_scale;

	sf::Sprite sprite;
	sf::Texture &texture;

	std::vector<sf::IntRect> sequence;
};