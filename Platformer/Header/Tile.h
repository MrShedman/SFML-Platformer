#pragma once

#include <SFML/Graphics.hpp>

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
	static sf::Vector2f texSize;
	const sf::Color color;
	const bool passable;
};

class Tile
{
public:

	Tile();

	Tile(sf::Vertex &quad, sf::FloatRect rect, TileProperty &properties);

	void update();

	Tile& operator = (Tile &rhs);

	TileProperty *properties;

	sf::FloatRect rect;

	sf::Vertex *quad;
};
