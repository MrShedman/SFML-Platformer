#include <iostream>

#include <TileMap.h>
#include <TileEditor.h>
#include <ResourceHolder.hpp>
#include <Utility.h>

TileMap::TileMap(State::Context context)
{
	window = context.window;

	Table = initializeTileData();
}

TileData& TileMap::getTileData(std::function<bool(TileData)> search)
{
	for (auto &data : Table)
	{
		if (search(data))
		{
			return data;
		}
	}

	// if we did not find the data default to air block
	return Table[Block::Air];
}

void TileMap::load(State::Context context)
{
	loadedLevel = context.levels->getID();

	file = context.levels->getFileName();
	width = context.levels->getWidth();
	height = context.levels->getHeight();

	std::vector<char> levelData = context.levels->getLevelData();

	vTiles.clear();
	vTiles.resize(width * height);

	std::cout << width;

	// populate the vertex array, with one quad per tile
	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			int id = x + y * width;
			vTiles[id] = Tile(static_cast<float>(x), static_cast<float>(y), getTileData([&](TileData data) { return data.txt == levelData[id]; }));
		}
	}
}

void TileMap::save()
{
	std::ofstream outfile(file);

	std::cout << "\nSaving map: " << file << std::endl;

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; ++i)
		{
			outfile << vTiles[i + j * width].data->txt;
		}

		outfile << std::endl;
	}

	outfile.close();
}

Levels::ID TileMap::getLevelID()
{
	return loadedLevel;
}

RectF TileMap::getBoundary()
{
	return RectF(0.f, static_cast<float>(getHeight()), 0.f, static_cast<float>(getWidth()));
}

int TileMap::getWidth() const
{
	return width * TileData::tileSize.x;
}

int TileMap::getHeight() const
{
	return height * TileData::tileSize.y;
}

int TileMap::getIndexXBiasLeft(float x) const
{
	int ix = static_cast<int>(x) / TileData::tileSize.x;

	if (ix * TileData::tileSize.x == x)
	{
		ix--;
	}
	return ix;	
}

int TileMap::getIndexXBiasRight(float x) const
{
	return static_cast<int>(x) / TileData::tileSize.x;
}

int TileMap::getIndexYBiasTop(float y) const
{
	int iy = static_cast<int>(y) / TileData::tileSize.y;

	if (iy * TileData::tileSize.y == y)
	{
		iy--;
	}
	return iy;
}

int TileMap::getIndexYBiasBottom(float y) const
{
	return static_cast<int>(y) / TileData::tileSize.y;
}

RectF TileMap::getCRect(int ix, int iy)
{
	return vTiles[ix + iy * width].rect;
}

Block::ID TileMap::getTileID(float x, float y)
{
	int id = getIndexXBiasRight(x) + getIndexYBiasBottom(y) * width;

	return vTiles[id].data->type;
}

void TileMap::modifyTile(float x, float y, Block::ID newBlock)
{
	modifyTile(getIndexXBiasRight(x), getIndexYBiasBottom(y), newBlock);
}

void TileMap::modifyTile(int ix, int iy, Block::ID newBlock)
{
	int id = ix + iy * width;

	vTiles[id].data = &getTileData([&](TileData data) { return data.type == newBlock; });
	vTiles[id].update();
}

void TileMap::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::S)
		{
			save();
		}
	}
}

void TileMap::update(float x, float y)
{

}

bool TileMap::isPickup(int ix, int iy)
{
	if (outOfRange(ix + iy * width, 0, width * height))
	{
		return false;
	}

	Block::ID type = vTiles[ix + iy * width].data->type;

	return (type == Block::YellowFlower || type == Block::RedFlower || type == Block::RedMushroom || type == Block::BrownMushroom);
}

bool TileMap::isHarmful(int ix, int iy)
{
	if (outOfRange(ix + iy * width, 0, width * height))
	{
		return false;
	}

	return vTiles[ix + iy * width].data->type == Block::Lava;
}

bool TileMap::isClimable(int ix, int iy)
{
	if (outOfRange(ix + iy * width, 0, width * height))
	{
		return false;
	}

	return vTiles[ix + iy * width].data->type == Block::Ladder;
}

bool TileMap::isPassable(int ix, int iy)
{
	if (outOfRange(ix + iy * width, 0, width * height))
	{
		return true;
	}

	return vTiles[ix + iy * width].data->passable;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//get chunk indices into which top left and bottom right points of view fall:
	sf::Vector2f temp = target.getView().getCenter() - (target.getView().getSize() / 2.f);//get top left point of view

	int left = getIndexXBiasLeft(temp.x);
	int top = getIndexYBiasTop(temp.y);

	temp += target.getView().getSize();//get bottom right point of view

	int right = getIndexXBiasRight(temp.x) + 1;
	int bottom = getIndexYBiasBottom(temp.y) + 1;

	clamp(left, 0, width);
	clamp(top, 0, height);
	clamp(right, 0, width);
	clamp(bottom, 0, height);

	for (int ix = left; ix < right; ++ix)
	{
		for (int iy = top; iy < bottom; ++iy)
		{
			target.draw(vTiles[ix + iy * width], states);
		}
	}
}

bool TileMap::getCRectSingle(CollisionRectF cRect, CollisionRectF &rect)
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