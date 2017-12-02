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
		ObsidianPassable,
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
		RedstoneTorch,
		IronBars,
		Fire,
		Spawner,
		Torch,
		TypeCount
	};
}

namespace BlockAnimation
{
	enum ID
	{
		Water,
		Lava,
		Fire,
		Portal,
		None,
		TypeCount
	};
}

class EnemyFactory;

class Tile : public sf::Drawable
{
public:

	virtual ~Tile();

	RectF rect;

	TileData *data;

	virtual void updatePosition();
	virtual void updateTexCoords();
	virtual void updateColor();

	sf::Vertex& getVertex(int i)
	{
		return quad[i];
	}

protected:

	Tile();

	Tile(float x, float y, TileData &data);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<sf::Vertex> quad;
};


class StaticTile : public Tile
{
public:

	StaticTile();

	StaticTile(float x, float y, TileData &data);

	StaticTile& operator = (StaticTile&& rhs);
};

class AnimatedTile : public Tile
{
public:

	AnimatedTile();

	AnimatedTile(float x, float y, TileData &data, TileAnimation &animation);

	AnimatedTile& operator = (AnimatedTile&& rhs);

	void updateTexCoords();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	TileAnimation *animation;
};

class SpawnerTile : public Tile
{
public:

	SpawnerTile();

	SpawnerTile(float x, float y, TileData &data, EnemyFactory &factory);

	~SpawnerTile();

	SpawnerTile& operator = (SpawnerTile&& rhs);

	EnemyFactory *factory;
};