#pragma once

#include <Tile.h>

sf::Vector2f TileProperty::texSize(64, 64);

Tile::Tile()
{
	properties = NULL;
}

Tile::Tile(sf::Vertex &quad, sf::FloatRect rect, TileProperty &properties)
:
quad(&quad),
rect(rect),
properties(&properties)
{
	update();
}

void Tile::update()
{
	sf::Vector2f t = properties->texCoords;
	sf::Vector2f s = sf::Vector2f(rect.width, rect.height);
	sf::Vector2f p = sf::Vector2f(rect.left, rect.top);

	quad[0].position = sf::Vector2f(p.x * s.x, p.y * s.y);
	quad[1].position = sf::Vector2f((p.x + 1) * s.x, p.y * s.y);
	quad[2].position = sf::Vector2f((p.x + 1) * s.x, (p.y + 1) * s.y);
	quad[3].position = sf::Vector2f(p.x * s.x, (p.y + 1) * s.y);

	s = TileProperty::texSize;

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