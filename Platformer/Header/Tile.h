#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <DataTables.hpp>
#include <Rect.h>

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
		Obsidian,
		Portal,
		RedFlower,
		YellowFlower,
		RedMushroom,
		BrownMushroom,
		Water,
		Lava,
		NetherRack,
		NetherBrick,
		SlowSand,
		GlowStone,
		TypeCount,
	};
}

class Tile : public sf::Drawable
{
public:

	Tile();

	Tile(float x, float y, TileData &data);

	Tile& operator=(Tile&& rhs);

	void update();

	TileData *data;

	RectF rect;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<sf::Vertex> quad;
};
