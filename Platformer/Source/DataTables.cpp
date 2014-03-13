#include <DataTables.hpp>
#include <Tile.h>

sf::Vector2i TileData::texSize = sf::Vector2i(64, 64);
sf::Vector2i TileData::tileSize = sf::Vector2i(48, 48);

std::vector<TileData> initializeTileData()
{
	std::vector<TileData> data(Block::TypeCount);

	data[Block::Air].type = Block::Air;
	data[Block::Air].txt = ' ';
	data[Block::Air].texCoords = sf::Vector2f(4, 11);
	data[Block::Air].color = sf::Color(255, 255, 255, 0);
	data[Block::Air].passable = true;

	data[Block::CobbleStone].type = Block::CobbleStone;
	data[Block::CobbleStone].txt = '^';
	data[Block::CobbleStone].texCoords = sf::Vector2f(0, 1);
	data[Block::CobbleStone].color = sf::Color(255, 255, 255, 255);
	data[Block::CobbleStone].passable = false;

	data[Block::Stone].type = Block::Stone;
	data[Block::Stone].txt = '*';
	data[Block::Stone].texCoords = sf::Vector2f(1, 0);
	data[Block::Stone].color = sf::Color(255, 255, 255, 255);
	data[Block::Stone].passable = false;

	data[Block::Dirt].type = Block::Dirt;
	data[Block::Dirt].txt = '+';
	data[Block::Dirt].texCoords = sf::Vector2f(2, 0);
	data[Block::Dirt].color = sf::Color(255, 255, 255, 255);
	data[Block::Dirt].passable = false;

	data[Block::Grass].type = Block::Grass;
	data[Block::Grass].txt = '~';
	data[Block::Grass].texCoords = sf::Vector2f(3, 0);
	data[Block::Grass].color = sf::Color(255, 255, 255, 255);
	data[Block::Grass].passable = false;

	data[Block::WoodPlank].type = Block::WoodPlank;
	data[Block::WoodPlank].txt = '!';
	data[Block::WoodPlank].texCoords = sf::Vector2f(4, 0);
	data[Block::WoodPlank].color = sf::Color(255, 255, 255, 255);
	data[Block::WoodPlank].passable = false;

	data[Block::StoneBrick].type = Block::StoneBrick;
	data[Block::StoneBrick].txt = '#';
	data[Block::StoneBrick].texCoords = sf::Vector2f(6, 3);
	data[Block::StoneBrick].color = sf::Color(255, 255, 255, 255);
	data[Block::StoneBrick].passable = false;

	data[Block::CrackedStone].type = Block::CrackedStone;
	data[Block::CrackedStone].txt = '?';
	data[Block::CrackedStone].texCoords = sf::Vector2f(5, 6);
	data[Block::CrackedStone].color = sf::Color(255, 255, 255, 255);
	data[Block::CrackedStone].passable = false;

	data[Block::Sand].type = Block::Sand;
	data[Block::Sand].txt = '"';
	data[Block::Sand].texCoords = sf::Vector2f(2, 1);
	data[Block::Sand].color = sf::Color(255, 255, 255, 255);
	data[Block::Sand].passable = false;

	data[Block::Gravel].type = Block::Gravel;
	data[Block::Gravel].txt = '£';
	data[Block::Gravel].texCoords = sf::Vector2f(3, 1);
	data[Block::Gravel].color = sf::Color(255, 255, 255, 255);
	data[Block::Gravel].passable = false;

	data[Block::Wood].type = Block::Wood;
	data[Block::Wood].txt = '$';
	data[Block::Wood].texCoords = sf::Vector2f(4, 1);
	data[Block::Wood].color = sf::Color(255, 255, 255, 255);
	data[Block::Wood].passable = false;

	data[Block::Ladder].type = Block::Ladder;
	data[Block::Ladder].txt = '|';
	data[Block::Ladder].texCoords = sf::Vector2f(3, 5);
	data[Block::Ladder].color = sf::Color(255, 255, 255, 255);
	data[Block::Ladder].passable = true;

	data[Block::MossyStone].type = Block::MossyStone;
	data[Block::MossyStone].txt = '/';
	data[Block::MossyStone].texCoords = sf::Vector2f(4, 6);
	data[Block::MossyStone].color = sf::Color(255, 255, 255, 255);
	data[Block::MossyStone].passable = false;

	data[Block::BedRock].type = Block::BedRock;
	data[Block::BedRock].txt = '%';
	data[Block::BedRock].texCoords = sf::Vector2f(1, 1);
	data[Block::BedRock].color = sf::Color(255, 255, 255, 255);
	data[Block::BedRock].passable = false;

	data[Block::Glass].type = Block::Glass;
	data[Block::Glass].txt = '&';
	data[Block::Glass].texCoords = sf::Vector2f(1, 3);
	data[Block::Glass].color = sf::Color(255, 255, 255, 255);
	data[Block::Glass].passable = false;

	data[Block::TallGrass].type = Block::TallGrass;
	data[Block::TallGrass].txt = '_';
	data[Block::TallGrass].texCoords = sf::Vector2f(7, 2);
	data[Block::TallGrass].color = sf::Color(180, 255, 90, 255);
	data[Block::TallGrass].passable = true;
	
	data[Block::Leaves].type = Block::Leaves;
	data[Block::Leaves].txt = '@';
	data[Block::Leaves].texCoords = sf::Vector2f(4, 3);
	data[Block::Leaves].color = sf::Color(180, 255, 90, 255);
	data[Block::Leaves].passable = false;

	data[Block::GoldOre].type = Block::GoldOre;
	data[Block::GoldOre].txt = '1';
	data[Block::GoldOre].texCoords = sf::Vector2f(0, 2);
	data[Block::GoldOre].color = sf::Color(255, 255, 255, 255);
	data[Block::GoldOre].passable = false;

	data[Block::IronOre].type = Block::IronOre;
	data[Block::IronOre].txt = '2';
	data[Block::IronOre].texCoords = sf::Vector2f(1, 2);
	data[Block::IronOre].color = sf::Color(255, 255, 255, 255);
	data[Block::IronOre].passable = false;

	data[Block::DiamondOre].type = Block::DiamondOre;
	data[Block::DiamondOre].txt = '3';
	data[Block::DiamondOre].texCoords = sf::Vector2f(2, 3);
	data[Block::DiamondOre].color = sf::Color(255, 255, 255, 255);
	data[Block::DiamondOre].passable = false;

	data[Block::RedstoneOre].type = Block::RedstoneOre;
	data[Block::RedstoneOre].txt = '4';
	data[Block::RedstoneOre].texCoords = sf::Vector2f(3, 3);
	data[Block::RedstoneOre].color = sf::Color(255, 255, 255, 255);
	data[Block::RedstoneOre].passable = false;

	data[Block::CoalOre].type = Block::CoalOre;
	data[Block::CoalOre].txt = '5';
	data[Block::CoalOre].texCoords = sf::Vector2f(2, 2);
	data[Block::CoalOre].color = sf::Color(255, 255, 255, 255);
	data[Block::CoalOre].passable = false;

	data[Block::Obsidian].type = Block::Obsidian;
	data[Block::Obsidian].txt = '6';
	data[Block::Obsidian].texCoords = sf::Vector2f(5, 2);
	data[Block::Obsidian].color = sf::Color(255, 255, 255, 255);
	data[Block::Obsidian].passable = false;

	data[Block::Portal].type = Block::Portal;
	data[Block::Portal].txt = 'p';
	data[Block::Portal].texCoords = sf::Vector2f(8, 2);
	data[Block::Portal].color = sf::Color(100, 50, 200, 200);
	data[Block::Portal].passable = true;

	data[Block::RedFlower].type = Block::RedFlower;
	data[Block::RedFlower].txt = '7';
	data[Block::RedFlower].texCoords = sf::Vector2f(12, 0);
	data[Block::RedFlower].color = sf::Color(255, 255, 255, 255);
	data[Block::RedFlower].passable = true;

	data[Block::YellowFlower].type = Block::YellowFlower;
	data[Block::YellowFlower].txt = '8';
	data[Block::YellowFlower].texCoords = sf::Vector2f(13, 0);
	data[Block::YellowFlower].color = sf::Color(255, 255, 255, 255);
	data[Block::YellowFlower].passable = true;

	data[Block::RedMushroom].type = Block::RedMushroom;
	data[Block::RedMushroom].txt = '9';
	data[Block::RedMushroom].texCoords = sf::Vector2f(12, 1);
	data[Block::RedMushroom].color = sf::Color(255, 255, 255, 255);
	data[Block::RedMushroom].passable = true;

	data[Block::BrownMushroom].type = Block::BrownMushroom;
	data[Block::BrownMushroom].txt = '¬';
	data[Block::BrownMushroom].texCoords = sf::Vector2f(13, 1);
	data[Block::BrownMushroom].color = sf::Color(255, 255, 255, 255);
	data[Block::BrownMushroom].passable = true;

	data[Block::Water].type = Block::Water;
	data[Block::Water].txt = 'W';
	data[Block::Water].texCoords = sf::Vector2f(13, 12);
	data[Block::Water].color = sf::Color(200, 200, 255, 255);
	data[Block::Water].passable = true;

	data[Block::Lava].type = Block::Lava;
	data[Block::Lava].txt = 'L';
	data[Block::Lava].texCoords = sf::Vector2f(13, 14);
	data[Block::Lava].color = sf::Color(255, 255, 255, 255);
	data[Block::Lava].passable = true;

	data[Block::NetherRack].type = Block::NetherRack;
	data[Block::NetherRack].txt = 'R';
	data[Block::NetherRack].texCoords = sf::Vector2f(7, 6);
	data[Block::NetherRack].color = sf::Color(255, 255, 255, 255);
	data[Block::NetherRack].passable = false;

	data[Block::NetherBrick].type = Block::NetherBrick;
	data[Block::NetherBrick].txt = 'B';
	data[Block::NetherBrick].texCoords = sf::Vector2f(0, 14);
	data[Block::NetherBrick].color = sf::Color(255, 255, 255, 255);
	data[Block::NetherBrick].passable = false;

	data[Block::SlowSand].type = Block::SlowSand;
	data[Block::SlowSand].txt = 'S';
	data[Block::SlowSand].texCoords = sf::Vector2f(8, 6);
	data[Block::SlowSand].color = sf::Color(255, 255, 255, 255);
	data[Block::SlowSand].passable = false;

	data[Block::GlowStone].type = Block::GlowStone;
	data[Block::GlowStone].txt = 'G';
	data[Block::GlowStone].texCoords = sf::Vector2f(9, 6);
	data[Block::GlowStone].color = sf::Color(255, 255, 255, 255);
	data[Block::GlowStone].passable = false;

	return data;
}
/*
void initializeTile(std::map<Block::ID, TileData> &mData)
{
	TileData Air;
	Air.txt = ' ';
	Air.texCoords = sf::Vector2f(4, 11);
	Air.color = sf::Color(255, 255, 255, 0);
	Air.passable = true;

	mData.insert(std::make_pair(Block::ID::Air, std::move(Air)));

	TileData CobbleStone;
	CobbleStone.txt = '^';
	CobbleStone.texCoords = sf::Vector2f(0, 1);
	CobbleStone.color = sf::Color(255, 255, 255, 255);
	CobbleStone.passable = false;

	mData.insert(std::make_pair(Block::ID::CobbleStone, std::move(CobbleStone)));
	
	TileData Stone;
	Stone.txt = '*';
	Stone.texCoords = sf::Vector2f(1, 0);
	Stone.color = sf::Color(255, 255, 255, 255);
	Stone.passable = false;

	mData.insert(std::make_pair(Block::ID::Stone, std::move(Stone)));

	TileData Dirt;
	Dirt.txt = '+';
	Dirt.texCoords = sf::Vector2f(2, 0);
	Dirt.color = sf::Color(255, 255, 255, 255);
	Dirt.passable = false;

	mData.insert(std::make_pair(Block::ID::Dirt, std::move(Dirt)));
	
	TileData Grass;
	Grass.txt = '~';
	Grass.texCoords = sf::Vector2f(3, 0);
	Grass.color = sf::Color(255, 255, 255, 255);
	Grass.passable = false;

	mData.insert(std::make_pair(Block::ID::Grass, std::move(Grass)));

	TileData WoodPlank;
	WoodPlank.txt = '!';
	WoodPlank.texCoords = sf::Vector2f(4, 0);
	WoodPlank.color = sf::Color(255, 255, 255, 255);
	WoodPlank.passable = false;

	mData.insert(std::make_pair(Block::ID::WoodPlank, std::move(WoodPlank)));

	TileData StoneBrick;
	StoneBrick.txt = '#';
	StoneBrick.texCoords = sf::Vector2f(6, 3);
	StoneBrick.color = sf::Color(255, 255, 255, 255);
	StoneBrick.passable = false;

	mData.insert(std::make_pair(Block::ID::StoneBrick, std::move(StoneBrick)));

	TileData CrackedStone;
	CrackedStone.txt = '?';
	CrackedStone.texCoords = sf::Vector2f(5, 6);
	CrackedStone.color = sf::Color(255, 255, 255, 255);
	CrackedStone.passable = false;

	mData.insert(std::make_pair(Block::ID::CrackedStone, std::move(CrackedStone)));

	TileData Sand;
	Sand.txt = '"';
	Sand.texCoords = sf::Vector2f(2, 1);
	Sand.color = sf::Color(255, 255, 255, 255);
	Sand.passable = false;

	mData.insert(std::make_pair(Block::ID::Sand, std::move(Sand)));

	TileData Gravel;
	Gravel.txt = '£';
	Gravel.texCoords = sf::Vector2f(3, 1);
	Gravel.color = sf::Color(255, 255, 255, 255);
	Gravel.passable = false;

	mData.insert(std::make_pair(Block::ID::Gravel, std::move(Gravel)));

	TileData Wood;
	Wood.txt = '$';
	Wood.texCoords = sf::Vector2f(4, 1);
	Wood.color = sf::Color(255, 255, 255, 255);
	Wood.passable = false;

	mData.insert(std::make_pair(Block::ID::Wood, std::move(Wood)));

	TileData Ladder;
	Ladder.txt = '|';
	Ladder.texCoords = sf::Vector2f(3, 5);
	Ladder.color = sf::Color(255, 255, 255, 255);
	Ladder.passable = true;

	mData.insert(std::make_pair(Block::ID::Ladder, std::move(Ladder)));

	TileData MossyStone;
	MossyStone.txt = '/';
	MossyStone.texCoords = sf::Vector2f(4, 6);
	MossyStone.color = sf::Color(255, 255, 255, 255);
	MossyStone.passable = false;

	mData.insert(std::make_pair(Block::ID::MossyStone, std::move(MossyStone)));

	TileData BedRock;
	BedRock.txt = '%';
	BedRock.texCoords = sf::Vector2f(1, 1);
	BedRock.color = sf::Color(255, 255, 255, 255);
	BedRock.passable = false;

	mData.insert(std::make_pair(Block::ID::BedRock, std::move(BedRock)));

	TileData Glass;
	Glass.txt = '&';
	Glass.texCoords = sf::Vector2f(1, 3);
	Glass.color = sf::Color(255, 255, 255, 255);
	Glass.passable = false;

	mData.insert(std::make_pair(Block::ID::Glass, std::move(Glass)));

	TileData TallGrass;
	TallGrass.txt = '_';
	TallGrass.texCoords = sf::Vector2f(7, 2);
	TallGrass.color = sf::Color(180, 255, 90, 255);
	TallGrass.passable = true;

	mData.insert(std::make_pair(Block::ID::TallGrass, std::move(TallGrass)));

	TileData Leaves;
	Leaves.txt = '@';
	Leaves.texCoords = sf::Vector2f(4, 3);
	Leaves.color = sf::Color(180, 255, 90, 255);
	Leaves.passable = false;

	mData.insert(std::make_pair(Block::ID::Leaves, std::move(Leaves)));

	TileData GoldOre;
	GoldOre.txt = '1';
	GoldOre.texCoords = sf::Vector2f(0, 2);
	GoldOre.color = sf::Color(255, 255, 255, 255);
	GoldOre.passable = false;

	mData.insert(std::make_pair(Block::ID::GoldOre, std::move(GoldOre)));

	TileData IronOre;
	IronOre.txt = '2';
	IronOre.texCoords = sf::Vector2f(1, 2);
	IronOre.color = sf::Color(255, 255, 255, 255);
	IronOre.passable = false;

	mData.insert(std::make_pair(Block::ID::IronOre, std::move(IronOre)));

	TileData DiamondOre;
	DiamondOre.txt = '3';
	DiamondOre.texCoords = sf::Vector2f(2, 3);
	DiamondOre.color = sf::Color(255, 255, 255, 255);
	DiamondOre.passable = false;

	mData.insert(std::make_pair(Block::ID::DiamondOre, std::move(DiamondOre)));

	TileData RedstoneOre;
	RedstoneOre.txt = '4';
	RedstoneOre.texCoords = sf::Vector2f(3, 3);
	RedstoneOre.color = sf::Color(255, 255, 255, 255);
	RedstoneOre.passable = false;

	mData.insert(std::make_pair(Block::ID::RedstoneOre, std::move(RedstoneOre)));

	TileData CoalOre;
	CoalOre.txt = '5';
	CoalOre.texCoords = sf::Vector2f(2, 2);
	CoalOre.color = sf::Color(255, 255, 255, 255);
	CoalOre.passable = false;

	mData.insert(std::make_pair(Block::ID::CoalOre, std::move(CoalOre)));

	TileData Obsidian;
	Obsidian.txt = '6';
	Obsidian.texCoords = sf::Vector2f(5, 2);
	Obsidian.color = sf::Color(255, 255, 255, 255);
	Obsidian.passable = false;

	mData.insert(std::make_pair(Block::ID::Obsidian, std::move(Obsidian)));

	TileData Portal;
	Portal.txt = 'p';
	Portal.texCoords = sf::Vector2f(8, 2);
	Portal.color = sf::Color(100, 50, 200, 200);
	Portal.passable = true;

	mData.insert(std::make_pair(Block::ID::Portal, std::move(Portal)));

	TileData RedFlower;
	RedFlower.txt = '7';
	RedFlower.texCoords = sf::Vector2f(12, 0);
	RedFlower.color = sf::Color(255, 255, 255, 255);
	RedFlower.passable = true;

	mData.insert(std::make_pair(Block::ID::RedFlower, std::move(RedFlower)));

	TileData YellowFlower;
	YellowFlower.txt = '8';
	YellowFlower.texCoords = sf::Vector2f(13, 0);
	YellowFlower.color = sf::Color(255, 255, 255, 255);
	YellowFlower.passable = true;

	mData.insert(std::make_pair(Block::ID::YellowFlower, std::move(YellowFlower)));

	TileData RedMushroom;
	RedMushroom.txt = '9';
	RedMushroom.texCoords = sf::Vector2f(12, 1);
	RedMushroom.color = sf::Color(255, 255, 255, 255);
	RedMushroom.passable = true;

	mData.insert(std::make_pair(Block::ID::RedMushroom, std::move(RedMushroom)));

	TileData BrownMushroom;
	BrownMushroom.txt = '¬';
	BrownMushroom.texCoords = sf::Vector2f(13, 1);
	BrownMushroom.color = sf::Color(255, 255, 255, 255);
	BrownMushroom.passable = true;

	mData.insert(std::make_pair(Block::ID::BrownMushroom, std::move(BrownMushroom)));

	TileData Water;
	Water.txt = 'W';
	Water.texCoords = sf::Vector2f(13, 12);
	Water.color = sf::Color(200, 200, 255, 255);
	Water.passable = true;

	mData.insert(std::make_pair(Block::ID::Water, std::move(Water)));

	TileData Lava;
	Lava.txt = 'L';
	Lava.texCoords = sf::Vector2f(13, 14);
	Lava.color = sf::Color(255, 255, 255, 255);
	Lava.passable = true;

	mData.insert(std::make_pair(Block::ID::Lava, std::move(Lava)));

	TileData NetherRack;
	NetherRack.txt = 'R';
	NetherRack.texCoords = sf::Vector2f(7, 6);
	NetherRack.color = sf::Color(255, 255, 255, 255);
	NetherRack.passable = false;

	mData.insert(std::make_pair(Block::ID::NetherRack, std::move(NetherRack)));

	TileData NetherBrick;
	NetherBrick.txt = 'B';
	NetherBrick.texCoords = sf::Vector2f(0, 14);
	NetherBrick.color = sf::Color(255, 255, 255, 255);
	NetherBrick.passable = false;

	mData.insert(std::make_pair(Block::ID::NetherBrick, std::move(NetherBrick)));

	TileData SlowSand;
	SlowSand.txt = 'S';
	SlowSand.texCoords = sf::Vector2f(8, 6);
	SlowSand.color = sf::Color(255, 255, 255, 255);
	SlowSand.passable = false;

	mData.insert(std::make_pair(Block::ID::SlowSand, std::move(SlowSand)));

	TileData GlowStone;
	GlowStone.txt = 'G';
	GlowStone.texCoords = sf::Vector2f(9, 6);
	GlowStone.color = sf::Color(255, 255, 255, 255);
	GlowStone.passable = false;

	mData.insert(std::make_pair(Block::ID::GlowStone, std::move(GlowStone)));
}*/