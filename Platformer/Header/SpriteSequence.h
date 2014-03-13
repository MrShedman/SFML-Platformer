#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include <BiDirection.h>

class SpriteSequence : public sf::Drawable, public sf::Transformable
{
public:
	SpriteSequence(sf::Texture &mTexture, int nFrames, int nHoldFrames, int nRow, int nColumn)
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

		for (int r = 0, dy = 10; r < nRow; ++r, dy += height)
		{
			for (int c = 0, dx = 10; c < nColumn; ++c, dx += width)
			{
				sequence.push_back(sf::IntRect(dx, dy, width - 20, height - 20));
			}
		}

		for (int i = 0; i < (nColumn * nRow) - nFrames; ++i)
		{
			sequence.pop_back();
		}

		sprite.setTextureRect(sequence.front());
		setOrigin(90, 90);
		setScale(m_scale, m_scale);
	}

	void advanceFrame(BiDirection d)
	{
		if (d.IsRight())
		{
			setScale(m_scale, m_scale);
		}
		else
		{
			setScale(-m_scale, m_scale);
		}

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