#include <iostream>

#include <TileMap.h>
#include <TileEditor.h>
#include <ResourceHolder.hpp>


TileMap::TileMap(State::Context context)
{
	window = context.window;

	m_tileset = context.textures->get(Textures::ID::TileMap);	

	Table = initializeTileData();
}

TileData& TileMap::getTileData(char c)
{
	for (auto &d : Table)
	{
		if (d.txt == c)
		{
			return d;
		}
	}

	return Table[Block::Air];
}

void TileMap::load(State::Context context, Levels::ID type)
{
	m_vertices.clear();
	vTiles.clear();

	file = context.levels->get(type).getFileName();
	
	width = context.levels->get(type).getWidth();
	height = context.levels->get(type).getHeight();

	std::vector<char> levelData = context.levels->get(type).getLevelData();

	m_vertices.resize(width * height * 4);
	vTiles.resize(width * height);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			int id = i + j * width;

			vTiles[id] = Tile(sf::Vector2f(i, j), getTileData(levelData[id]));
		}
	}
}

void TileMap::save()
{
	std::ofstream outfile(file);

	std::cout << "\nSaving map: " << file << std::endl;

	for (unsigned int j = 0; j < height; ++j)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			outfile << vTiles[i + j * width].data->txt;
		}

		outfile << std::endl;
	}

	outfile.close();
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
	int ix = x / TileData::tileSize.x;

	if (ix * TileData::tileSize.x == x)
	{
		ix--;
	}
	return ix;	
}

int TileMap::getIndexXBiasRight(float x) const
{
	return x / TileData::tileSize.x;
}

int TileMap::getIndexYBiasTop(float y) const
{
	int iy = y / TileData::tileSize.y;

	if (iy * TileData::tileSize.y == y)
	{
		iy--;
	}
	return iy;
}

int TileMap::getIndexYBiasBottom(float y) const
{
	return y / TileData::tileSize.y;
}

RectF TileMap::getCRect(int ix, int iy)
{
	return vTiles[ix + iy * width].rect;
}

void TileMap::modifyTile(int x, int y, TileData &prop)
{
	int id = getIndexXBiasRight(x) + getIndexYBiasBottom(y) * width;

	vTiles[id].data = &prop;
	vTiles[id].update();
}

void TileMap::pollEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::S)
		{
			save();
		}
	}
}

void TileMap::update()
{

}

bool TileMap::isPassable(int ix, int iy)
{
	if ((ix + iy * width) >= vTiles.size())
	{
		return true;
	}
	return vTiles[ix + iy * width].data->passable;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	int left = 0, right = 0, top = 0, bottom = 0;
	//get chunk indices into which top left and bottom right points of view fall:
	sf::Vector2f temp = target.getView().getCenter() - (target.getView().getSize() / 2.f);//get top left point of view

	left = static_cast<int>(temp.x / (TileData::tileSize.x));
	top = static_cast<int>(temp.y / (TileData::tileSize.y));

	temp += target.getView().getSize();//get bottom right point of view

	right = 1 + static_cast<int>(temp.x / (TileData::tileSize.x));
	bottom = 1 + static_cast<int>(temp.y / (TileData::tileSize.y));

	//clamp these to fit into array bounds:
	left = std::max(0, std::min(left, width));
	top = std::max(0, std::min(top, height));
	right = std::max(0, std::min(right, width));
	bottom = std::max(0, std::min(bottom, height));

	states.texture = &m_tileset;

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

void TileMap::getCRectList(RectF cRect, std::vector<RectF> &list)
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