#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "SpriteSequence.h"
#include "SpriteCore.h"
#include <SpriteState.h>

class Sprite : public sf::Drawable
{
public:
	virtual ~Sprite(){}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	SpriteState& GetState();

	CollisionRectF getCRect() const
	{
		return core.getCRect();
	}

	bool isAlive()
	{
		return core.health > 0;
	}

	float getX()
	{
		return core.x;
	}

	float getY()
	{
		return core.y;
	}

	float getVX()
	{
		return core.vx;
	}

	float getVY()
	{
		return core.vy;
	}

public:

	SpriteCore core;
};