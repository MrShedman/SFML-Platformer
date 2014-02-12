#pragma once

#include <SFML/Graphics.hpp>

#include <DataTables.hpp>
#include <RectF.h>

namespace Block
{
	enum ID
	{
		Air,
		CobbleStone,
		Stone,
		Dirt,
		Grass,
		WoodPlank,
		StoneBrick,
		CrackedStone,
		Sand,
		Gravel,
		Wood,
		Ladder,
		MossyStone,
		BedRock,
		Glass,
		TallGrass,
		Leaves,
		GoldOre,
		IronOre,
		DiamondOre,
		RedstoneOre,
		CoalOre,
		TypeCount,
	};
}

class Tile
{
public:

	Tile();

	Tile(sf::Vertex &quad, sf::Vector2f position, TileData &data);

	void update();

	Tile& operator = (Tile &rhs);

	TileData *data;

	RectF rect;

	sf::Vertex *quad;
};
