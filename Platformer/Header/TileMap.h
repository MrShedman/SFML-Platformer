#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <Tile.h>
#include <CollisionRectF.h>

	
class TileMap : public sf::Drawable
{
public:

	void setWindow(sf::RenderWindow &win)
	{
		window = &win;
		block = 0;
	}

	TileProperty& getTileProperty(char c);

	TileProperty& getTileProperty(unsigned int i);

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

	void getCRectList(RectF cRect, std::vector<RectF> &list)
	{
		for (int iy = getIndexYBiasBottom(cRect.top), iyEnd = getIndexYBiasTop(cRect.bottom); iy <= iyEnd; ++iy)
		{
			for (int ix = getIndexXBiasRight(cRect.left), ixEnd = getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
			{
				if (!isPassable(ix, iy))
				{
					list.push_back(getCRect(ix, iy));
				}
			}
		}
	}

	void pollEvent(sf::Event &event);

	bool isPassable(int ix, int iy);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string file;

	int width;
	int height;

	unsigned int block;

	std::vector<Tile> vTiles;
	sf::VertexArray m_vertices;
	std::vector<TileProperty> vTileProperty;
	sf::Texture m_tileset;

	sf::RenderWindow *window;
};