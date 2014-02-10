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

TileProperty& TileMap::getTileProperty(int i)
{
	for (auto &p : vTileProperty)
	{
		if (p.ID == i)
		{
			return p;
		}
	}

	return TileProperty(TRANSPARENT);
}

void TileMap::load(std::string levelName, sf::Vector2f windowSize)
{
	tileID = 1;

	m_tileset.loadFromFile("Textures/terrain.png");
	tileSelect.setTexture(m_tileset);

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
	vTileProperty.push_back(TileProperty(GLASS));
	vTileProperty.push_back(TileProperty(TALL_GRASS));
	vTileProperty.push_back(TileProperty(LEAVES));
	vTileProperty.push_back(TileProperty(LADDER));
	vTileProperty.push_back(TileProperty(GOLD_ORE));
	vTileProperty.push_back(TileProperty(IRON_ORE));
	vTileProperty.push_back(TileProperty(DIAMOND_ORE));
	vTileProperty.push_back(TileProperty(REDSTONE_ORE));
	vTileProperty.push_back(TileProperty(COAL_ORE));

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);
	vTiles.resize(width * height);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			int id = i + j * width;
			vTiles[id] = Tile(m_vertices[(id)* 4], sf::Vector2f(i, j), getTileProperty(cTiles[id]));
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
			outfile << vTiles[i + j * width].properties->txt;
		}

		outfile << std::endl;
	}

	outfile.close();
}

int TileMap::getIndexXBiasLeft(float x) const
{
	int ix = x / TileProperty::tileSize.x;

	if (ix * TileProperty::tileSize.x == x)
	{
		ix--;
	}
	return ix;	
}

int TileMap::getIndexXBiasRight(float x) const
{
	return x / TileProperty::tileSize.x;
}

int TileMap::getIndexYBiasTop(float y) const
{
	int iy = y / TileProperty::tileSize.y;

	if (iy * TileProperty::tileSize.y == y)
	{
		iy--;
	}
	return iy;
}

int TileMap::getIndexYBiasBottom(float y) const
{
	return y / TileProperty::tileSize.y;
}

void TileMap::modifyTile(int x, int y, TileProperty prop)
{
	int id = getIndexXBiasRight(x) + getIndexYBiasBottom(y) * width;

	vTiles[id].properties = &getTileProperty(prop.txt);
	vTiles[id].update();
}

void TileMap::pollEvent(sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::S)
		{
			save();
		}
		if (event.key.code == sf::Keyboard::E)
		{
			editing = !editing;
		}
	}

	if (!editing)
	{
		return;
	}

	sf::Vector2f mPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	tileSelect.setPosition(mPos + sf::Vector2f(20, 20));
	outline.setPosition(tileSelect.getPosition());

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			modifyTile(mPos.x, mPos.y, getTileProperty(tileID));
		}
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			modifyTile(mPos.x, mPos.y, TileProperty(TRANSPARENT));
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			tileID = getTile(mPos.x, mPos.y)->properties->ID;
		}
	}
	if (event.type == sf::Event::MouseWheelMoved)
	{
		int size = vTileProperty.size();

		tileID += event.mouseWheel.delta;

		if (tileID >= 0)
		{
			tileID %= size;
		}
		else
		{
			tileID = size - std::abs(tileID % size) % size;
		}
	}
}

void TileMap::update()
{
	sf::Vector2f mPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	tileSelect.setPosition(mPos + sf::Vector2f(20, 20));
	outline.setPosition(tileSelect.getPosition());

	updateOverlay();
}

void TileMap::updateOverlay()
{
	sf::Vector2f t = getTileProperty(tileID).texCoords;
	sf::Vector2f size = TileProperty::texSize;
	sf::Vector2f padding((t.x * 2 + 1) * 4, (t.y * 2 + 1) * 4);
	sf::Vector2f position = sf::Vector2f(t.x * size.x, t.y * size.y) + padding;

	outline.setSize(size);
	outline.setOutlineThickness(5.f);
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(sf::Color::Black);
	outline.setScale(0.6f, 0.6f);
	tileSelect.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(position), static_cast<sf::Vector2i>(size)));
	tileSelect.setScale(0.6f, 0.6f);
}

bool TileMap::isPassable(int ix, int iy)
{
	return vTiles[ix + iy * width].properties->passable;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_vertices, &m_tileset);
	
	if (editing)
	{
		target.draw(tileSelect);
		target.draw(outline);
	}
}