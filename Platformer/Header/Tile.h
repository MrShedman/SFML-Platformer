#pragma once

#include <SFML/Graphics.hpp>

#include <RectF.h>

class TileProperty
{
	public:
	TileProperty(int ID, sf::Vector2f texCoords, char txt, sf::Color color, bool passable)
	:
	ID(ID),
	texCoords(texCoords),
	txt(txt),
	color(color),
	passable(passable)
	{}

	const int ID;
	const char txt;
	const sf::Vector2f texCoords;
	const sf::Color color;
	const bool passable;

	static sf::Vector2f texSize;
	static sf::Vector2f tileSize;
};

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
