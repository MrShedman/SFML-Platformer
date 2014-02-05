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

	int getIndexXBiasLeft(float x) const;

	int getIndexXBiasRight(float x) const;

	int getIndexYBiasTop(float y) const;

	int getIndexYBiasBottom(float y) const;

	int getWidth() const
	{
		return width * TileProperty::tileSize.x;
	}

	int getHeight() const
	{
		return height * TileProperty::tileSize.y;
	}

	void modifyTile(int x, int y, TileProperty prop);

	void print();

	RectF getCRect(int ix, int iy)
	{
		return vTiles[ix + iy * width].rect;
	}

	bool getCRectSingle(CollisionRectF cRect, CollisionRectF &rect)
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

	int width;
	int height;

	std::vector<Tile> vTiles;
	sf::VertexArray m_vertices;
	std::vector<TileProperty> vTileProperty;
	sf::Texture m_tileset;

	sf::RenderWindow *window;
};