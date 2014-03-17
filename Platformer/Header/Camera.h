#pragma once

#include <SFML/Graphics.hpp>

#include <Sprite.h>
#include <Rect.h>
#include <utility>

class Camera
{
public:

	void setSpriteToFollow(Sprite &sprite)
	{
		this->sprite = &sprite;
	}

	void setViewSize(sf::Vector2f size)
	{
		sf::FloatRect visibleArea(0, 0, size.x, size.y);
		view.reset(visibleArea);
	}

	void setViewBoundary(RectF boundary)
	{
		this->boundary = boundary;
	}

	void updatePosition(sf::Time dt)
	{
		float x = sprite->core.x - view.getCenter().x;
		float y = sprite->core.lastPlatformHeight - view.getCenter().y - 0.2f * view.getSize().y;

		if (std::abs(sprite->core.lastPlatformHeight - sprite->core.y - 6 * 48) > view.getSize().y / 2.f)
		{
			y = sprite->core.y - view.getCenter().y + 5 * 48;
		}

		if (sprite->core.canClimb)
		{
			y = sprite->core.y - view.getCenter().y;
		}

		if (!sprite->isAlive())
		{
			y = 0.f;
		}

		float dx = dt.asSeconds() * 2.f + (std::abs(sprite->core.vx) * 0.005f);
		float dy = dt.asSeconds() * 3.f;

		x *= dx;
		y *= dy;

		x = floorf(x * 10.f + 0.5f) / 10.f;
		y = floorf(y * 10.f + 0.5f) / 10.f;

		float nx = view.getCenter().x + x;
		float ny = view.getCenter().y + y;

		clamp(nx, boundary.left + view.getSize().x / 2.f, boundary.right - view.getSize().x / 2.f);
		clamp(ny, boundary.top + view.getSize().y / 2.f, boundary.bottom - view.getSize().y / 2.f);

		view.setCenter(nx, ny);
	}

	const sf::View getView() const
	{
		return view;
	}

private:
	RectF boundary;
	Sprite *sprite;
	sf::View view;
};