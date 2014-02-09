#pragma once

#include <SFML/Graphics.hpp>

#include <TileProperty.h>
#include <RectF.h>

class Tile
{
public:

	Tile();

	Tile(sf::Vertex &quad, sf::Vector2f position, TileProperty &properties);

	void update();

	Tile& operator = (Tile &rhs);

	TileProperty *properties;

	RectF rect;

	sf::Vertex *quad;
};
