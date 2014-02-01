#pragma once

#include <iostream>

#include <TileMap.h>

TileProperty& TileMap::getTileProperty(char c)
{
	for (auto &p : vTileProperty)
	{
		if (p.txt == c)
		{
			return p;
		}
	}

	return TileProperty(TRANSPARENT);
}

void TileMap::load(std::string levelName, sf::Vector2f windowSize)
{
	m_tileset.loadFromFile("Textures/terrain.png");
	//m_tileset.setSmooth(true);
	//m_tileset.setRepeated(true);

	file = levelName;
	std::ifstream infile(file);
	std::string line;
	std::vector<char> cTiles;

	if (!infile.is_open())
	{
		std::cout << "ERROR: level does not exist!" << std::endl;
		return;
	}
	else
	{
		std::cout << "Loaded map: " << file << std::endl;
	}

	unsigned int nTiles = 0;
	unsigned int nRows = 0;
	unsigned int nColumns = 0;

	while (std::getline(infile, line))
	{
		nColumns = line.length();
		std::istringstream iss(line);

		char t;

		while (iss >> std::noskipws >> t)
		{
			cTiles.push_back(t);
		}
		nRows++;
	}

	nTiles = cTiles.size();

	std::cout << "\nTiles: " << nTiles << "\nnColumns: " << nColumns << "\nnRows: " << nRows << std::endl;

	width = nColumns;
	height = nRows;

	tileSize.x = std::max(windowSize.x / width, windowSize.y / height);
	tileSize.y = tileSize.x;

	vTileProperty.push_back(TileProperty(TRANSPARENT));
	vTileProperty.push_back(TileProperty(COBBLESTONE));
	vTileProperty.push_back(TileProperty(STONE));
	vTileProperty.push_back(TileProperty(DIRT));
	vTileProperty.push_back(TileProperty(GRASS));
	vTileProperty.push_back(TileProperty(WOOD_PLANK));
	vTileProperty.push_back(TileProperty(STONE_BRICK));
	vTileProperty.push_back(TileProperty(CRACKED_STONE));
	vTileProperty.push_back(TileProperty(WOOD));
	vTileProperty.push_back(TileProperty(SAND));
	vTileProperty.push_back(TileProperty(GRAVEL));
	vTileProperty.push_back(TileProperty(MOSSY_STONE));
	vTileProperty.push_back(TileProperty(BEDROCK));

	vTiles.resize(width * height);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			vTiles[i + j * width].setSize(tileSize);
			vTiles[i + j * width] = Tile(sf::Vector2f(i, j), m_tileset, getTileProperty(cTiles[i + j * width]));
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
			outfile << vTiles[(i + j * width)].properties->txt;
		}

		outfile << std::endl;
	}

	outfile.close();
}

int TileMap::getIndexXBiasLeft(float x)
{
	int ix = x / tileSize.x;

	if (ix * tileSize.x == x)
	{
		ix--;
	}
	return ix;
}

int TileMap::getIndexXBiasRight(float x)
{
	return x / tileSize.x;
}

int TileMap::getIndexYBiasTop(float y)
{
	int iy = y / tileSize.y;

	if (iy * tileSize.y == y)
	{
		iy--;
	}
	return iy;
}

int TileMap::getIndexYBiasBottom(float y)
{
	return y / tileSize.y;
}

void TileMap::modifyTile(int x, int y, TileProperty prop)
{
	int id = getIndexXBiasRight(x) + getIndexYBiasBottom(y) * width;

	vTiles[id].properties = &getTileProperty(prop.txt);
	vTiles[id].update();
}

void TileMap::print()
{
	for (auto &i : vTiles)
	{
		std::cout << i.properties->passable << std::endl;
	}
}

void TileMap::pollEvent(sf::Event &event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2f pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		if (event.mouseButton.button == sf::Mouse::Left)
		{
			modifyTile(pos.x, pos.y, TileProperty(GRASS));
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			modifyTile(pos.x, pos.y, TileProperty(TRANSPARENT));
		}
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::S)
		{
			save();
		}
		if (event.key.code == sf::Keyboard::P)
		{
			print();
		}
	}
}

bool TileMap::isPassable(int ix, int iy)
{
	return vTiles[ix + iy * width].properties->passable;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto &t : vTiles)
	{
		target.draw(t);
	}
}
