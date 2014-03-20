#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <Tile.h>
#include <CollisionRectF.h>
#include <State.hpp>
#include <Level.h>
#include <ResourceIdentifiers.hpp>

class TileMap : public sf::Drawable
{
public:
	
	TileMap(State::Context context);

	TileData& getTileData(char c);

	TileData& getTileData(Block::ID type);

	void load(State::Context context);

	void save();

	int getIndexXBiasLeft(float x) const;

	int getIndexXBiasRight(float x) const;

	int getIndexYBiasTop(float y) const;

	int getIndexYBiasBottom(float y) const;

	RectF getBoundary();

	int getWidth() const;

	int getHeight() const;

	Block::ID getTileID(float x, float y);

	void modifyTile(float x, float y, Block::ID newBlock);

	void modifyTile(int ix, int iy, Block::ID newBlock);

	Levels::ID getLevelID();

	RectF getCRect(int ix, int iy);

	bool getCRectSingle(CollisionRectF cRect, CollisionRectF &rect);

	void handleEvent(const sf::Event &event);

	bool isPickup(int ix, int iy);

	bool isHarmful(int ix, int iy);

	bool isClimable(int ix, int iy);

	bool isPassable(int ix, int iy);

	void update(float x, float y);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string file;

	int width;
	int height;

	Levels::ID loadedLevel;

	std::vector<TileData> Table;
	std::vector<Tile> vTiles;

	sf::RenderWindow *window;
};