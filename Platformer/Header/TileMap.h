#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <Sprite.h>
#include <Tile.h>

#define TRANSPARENT			0, sf::Vector2f(5, 2), ' ', sf::Color(255, 255, 255, 255), true
#define COBBLESTONE			1, sf::Vector2f(0, 0), '^', sf::Color(255, 255, 255, 255), false
#define STONE				2, sf::Vector2f(1, 0), '*', sf::Color(255, 255, 255, 255), false
#define DIRT				3, sf::Vector2f(2, 0), '+', sf::Color(255, 255, 255, 255), false
#define GRASS				4, sf::Vector2f(3, 0), '~', sf::Color(255, 255, 255, 255), false
#define WOOD_PLANK			5, sf::Vector2f(4, 0), '!', sf::Color(255, 255, 255, 255), false
#define STONE_BRICK			6, sf::Vector2f(0, 1), '#', sf::Color(255, 255, 255, 255), false
#define CRACKED_STONE		7, sf::Vector2f(1, 1), '?', sf::Color(255, 255, 255, 255), false
#define SAND				8, sf::Vector2f(2, 1), '"', sf::Color(255, 255, 255, 255), false
#define GRAVEL				9, sf::Vector2f(3, 1), '£', sf::Color(255, 255, 255, 255), false
#define WOOD				10, sf::Vector2f(4, 1), '$', sf::Color(255, 255, 255, 255), false
#define MOSSY_STONE			11, sf::Vector2f(0, 2), '/', sf::Color(255, 255, 255, 255), false
#define BEDROCK				12, sf::Vector2f(1, 2), '%', sf::Color(255, 255, 255, 255), false
	
class TileMap : public sf::Drawable
{
public:

	void setWindow(sf::RenderWindow &win)
	{
		window = &win;
	}

	TileProperty& getTileProperty(char c);

	void load(std::string levelName, sf::Vector2f windowSize);

	void save();

	int getIndexXBiasLeft(float x);

	int getIndexXBiasRight(float x);

	int getIndexYBiasTop(float y);

	int getIndexYBiasBottom(float y);

	int getWidth() const
	{
		return width * tileSize.x;
	}

	void modifyTile(int x, int y, TileProperty prop);

	void print();

	RectF getCRect(int ix, int iy)
	{
		Tile* tile = &vTiles[ix + iy * width];

		int top = tile->quad[0].position.y;
		int bottom = tile->quad[2].position.y;
		int left = tile->quad[0].position.x;
		int right = tile->quad[1].position.x;

		return RectF(top, bottom, left, right);
	}

	bool getCRectSingle(CollisionRectF cRect, RectF &rect)
	{
		if (cRect.vx > 0.f)
		{
			if (cRect.vy > 0.f)
			{
				for (int iy = getIndexYBiasBottom(cRect.top), iyEnd = getIndexYBiasTop(cRect.bottom); iy <= iyEnd; ++iy)
				{
					for (int ix = getIndexXBiasRight(cRect.left), ixEnd = getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
					{
						if (!isPassable(ix, iy))
						{
							rect = getCRect(ix, iy);
							return true;
						}
					}
				}
			}
			else
			{
				for (int iy = getIndexYBiasTop(cRect.bottom), iyEnd = getIndexYBiasBottom(cRect.top); iy >= iyEnd; --iy)
				{
					for (int ix = getIndexXBiasRight(cRect.left), ixEnd = getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
					{
						if (!isPassable(ix, iy))
						{
							rect = getCRect(ix, iy);
							return true;
						}
					}
				}
			}
		}
		else
		{
			if (cRect.vy > 0.f)
			{
				for (int iy = getIndexYBiasBottom(cRect.top), iyEnd = getIndexYBiasTop(cRect.bottom); iy <= iyEnd; ++iy)
				{
					for (int ix = getIndexXBiasLeft(cRect.right), ixEnd = getIndexXBiasRight(cRect.left); ix >= ixEnd; --ix)
					{
						if (!isPassable(ix, iy))
						{
							rect = getCRect(ix, iy);
							return true;
						}
					}
				}
			}
			else
			{
				for (int iy = getIndexYBiasTop(cRect.bottom), iyEnd = getIndexYBiasBottom(cRect.top); iy >= iyEnd; --iy)
				{
					for (int ix = getIndexXBiasLeft(cRect.right), ixEnd = getIndexXBiasRight(cRect.left); ix >= ixEnd; --ix)
					{
						if (!isPassable(ix, iy))
						{
							rect = getCRect(ix, iy);
							return true;
						}
					}
				}
			}
		}

		return false;
	}

	void pollEvent(sf::Event &event);

	bool isPassable(int ix, int iy);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string file;

	sf::Vector2f tileSize;

	int width;
	int height;

	std::vector<Tile> vTiles;
	std::vector<TileProperty> vTileProperty;
	sf::Texture m_tileset;

	sf::RenderWindow *window;
};