#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <Tile.h>
#include <TileEditor.h>
#include <CollisionRectF.h>
#include <State.hpp>
#include <ResourceIdentifiers.hpp>

class TileMap : public sf::Drawable
{
public:

	friend class TileEditor;

	TileMap(State::Context context);

	TileData& getTileData(char c);

	void load(std::string levelName);

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

	void pollEvent(const sf::Event &event);

	bool isPassable(int ix, int iy);

	void updateOverlay();

	void update();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string file;

	int width;
	int height;

	TileEditor editor;

	std::vector<TileData> Table;
	std::vector<std::unique_ptr<Tile>> vTiles;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	sf::RenderWindow *window;
};