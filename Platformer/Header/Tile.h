#pragma once

#include <SFML/Graphics.hpp>

struct TileProperty
{
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

class Tile : public sf::Drawable
{
public:

	Tile();

	Tile(sf::Vector2f position, sf::Texture &texture, TileProperty &properties);

	static void setSize(sf::Vector2f s);

	void update();

	Tile& operator = (Tile &rhs);

	TileProperty *properties;

	sf::Vector2f position;
	static sf::Vector2f size;

	sf::VertexArray quad;
	sf::Texture *tileset;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
