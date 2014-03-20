#pragma once

#include <ResourceIdentifiers.hpp>

#include <SFML/Graphics.hpp>

#include <vector>
#include <map>

namespace Block
{
	enum ID;
}

struct TileData
{
	Block::ID type;
	char txt;
	sf::Vector2f texCoords;
	sf::Color color;
	bool passable;

	static sf::Vector2i texSize;
	static sf::Vector2i tileSize;
};

std::vector<TileData>	initializeTileData();