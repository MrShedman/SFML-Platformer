#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include <BiDirection.h>

class SpriteSequence : public sf::Drawable, public sf::Transformable
{
public:
	SpriteSequence(std::string file, unsigned int nFrames, unsigned int nHoldFrames, unsigned int nRow, unsigned int nColumn)
		:
		nFrames(nFrames),
		nHoldFrames(nHoldFrames),
		index(0),
		scale(0.72f)
	{
		texture.loadFromFile(file);
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
		sprite.setOrigin(90, 90);
		sprite.setScale(scale, scale);
	}

	void advance(float x, float y, BiDirection d)
	{
		if (d.IsRight())
		{
			sprite.setScale(scale, scale);
		}
		else
		{
			sprite.setScale(-scale, scale);
		}

		curHoldCount++;

		if (curHoldCount >= nHoldFrames)
		{
			index++;
			index %= nFrames;
			curHoldCount = 0;
		}

		sprite.setTextureRect(sequence[index]);
		sprite.setPosition(x, y);
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

	unsigned int nHoldFrames;
	unsigned int nFrames;
	unsigned int index;
	unsigned int curHoldCount;

	const float scale;

	sf::Sprite sprite;
	sf::Texture texture;

	std::vector<sf::IntRect> sequence;
};