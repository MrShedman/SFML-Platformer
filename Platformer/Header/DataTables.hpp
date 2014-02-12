#pragma once

#include <ResourceIdentifiers.hpp>

#include <SFML/Graphics.hpp>

#include <vector>

struct TileData
{
	int ID;
	char txt;
	sf::Vector2f texCoords;
	sf::Color color;
	bool passable;

	static sf::Vector2f texSize;
	static sf::Vector2f tileSize;
};

std::vector<TileData>	initializeTileData();