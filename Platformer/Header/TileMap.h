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

	friend class TileEditor;

	TileMap(State::Context context);

	TileData& getTileData(char c);

	void load(State::Context context, Levels::ID type);

	void save();

	int getIndexXBiasLeft(float x) const;

	int getIndexXBiasRight(float x) const;

	int getIndexYBiasTop(float y) const;

	int getIndexYBiasBottom(float y) const;

	int getWidth() const;

	int getHeight() const;

	void modifyTile(int x, int y, TileData &prop);

	RectF getCRect(int ix, int iy);

	bool getCRectSingle(CollisionRectF cRect, CollisionRectF &rect);

	void getCRectList(RectF cRect, std::vector<RectF> &list);

	void handleEvent(const sf::Event &event);

	bool isPassable(int ix, int iy);

	void update(float x, float y);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string file;

	int width;
	int height;

	std::vector<TileData> Table;
	std::vector<Tile> vTiles;
	sf::Texture m_tileset;

	sf::RenderWindow *window;
};