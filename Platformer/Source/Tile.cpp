#pragma once

#include <Tile.h>

sf::Vector2f TileProperty::texSize(64, 64);
sf::Vector2f TileProperty::tileSize(40, 40);

Tile::Tile()
{
	properties = NULL;
}

Tile::Tile(sf::Vertex &quad, sf::Vector2f position, TileProperty &properties)
:
quad(&quad),
rect(position.y * TileProperty::tileSize.y, (position.y + 1) * TileProperty::tileSize.y, position.x * TileProperty::tileSize.x, (position.x + 1) * TileProperty::tileSize.x),
properties(&properties)
{
	update();
}

void Tile::update()
{
	quad[0].position = sf::Vector2f(rect.left, rect.top);
	quad[1].position = sf::Vector2f(rect.right, rect.top);
	quad[2].position = sf::Vector2f(rect.right, rect.bottom);
	quad[3].position = sf::Vector2f(rect.left, rect.bottom);

	sf::Vector2f t = properties->texCoords;
	sf::Vector2f s = TileProperty::texSize;

	quad[0].texCoords = sf::Vector2f(t.x * s.x + 1, t.y * s.y + 1);
	quad[1].texCoords = sf::Vector2f((t.x + 1) * s.x - 1, t.y * s.y + 1);
	quad[2].texCoords = sf::Vector2f((t.x + 1) * s.x - 1, (t.y + 1) * s.y - 1);
	quad[3].texCoords = sf::Vector2f(t.x * s.x + 1, (t.y + 1) * s.y - 1);

	quad[0].color = properties->color;
	quad[1].color = properties->color;
	quad[2].color = properties->color;
	quad[3].color = properties->color;
}

Tile& Tile::operator = (Tile &rhs)
{
	quad = rhs.quad;

	rect = rhs.rect;

	properties = rhs.properties;

	update();

	return *this;
}