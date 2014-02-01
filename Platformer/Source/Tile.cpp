#pragma once

#include <Tile.h>

sf::Vector2f TileProperty::texSize(64, 64);

sf::Vector2f Tile::size;

Tile::Tile()
{
	tileset = NULL;
	properties = NULL;

	quad.setPrimitiveType(sf::Quads);
	quad.resize(4);
}

Tile::Tile(sf::Vector2f position, sf::Texture &texture, TileProperty &properties)
:
position(position),
tileset(&texture),
properties(&properties)
{
	quad.setPrimitiveType(sf::Quads);
	quad.resize(4);

	update();
}

void Tile::setSize(sf::Vector2f s)
{
	size = s;
}

void Tile::update()
{
	sf::Vector2f t = properties->texCoords;
	sf::Vector2f s = size;

	quad[0].position = sf::Vector2f(position.x * s.x, position.y * s.y);
	quad[1].position = sf::Vector2f((position.x + 1) * s.x, position.y * s.y);
	quad[2].position = sf::Vector2f((position.x + 1) * s.x, (position.y + 1) * s.y);
	quad[3].position = sf::Vector2f(position.x * s.x, (position.y + 1) * s.y);

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
	position = rhs.position;

	properties = rhs.properties;
	tileset = rhs.tileset;

	update();

	return *this;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = tileset;

	target.draw(quad, states);
}