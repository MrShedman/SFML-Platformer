#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>

#include <SFML/Graphics.hpp>

#include <Tile.h>
#include <CollisionRectF.h>
#include <State.hpp>
#include <Level.h>
#include <ResourceIdentifiers.hpp>

#include <TileAnimation.h>
#include <LightManager.h>
#include <SoftShadow.h>

class TileMap : public sf::Drawable
{
public:
	
	TileMap(State::Context context, EnemyFactory &eFactory);

	TileData& getTileData(std::function<bool(TileData)> search);

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

	void addAnimation(int id);

	void removeAnimation(int id);

	void addLight(int id);

	void removeLight(int id);

	Levels::ID getLevelID();
	
	Tile &getTile(int ix, int iy) const;

	RectF getCRect(int ix, int iy);

	RectI getDrawingRect(sf::RenderTarget& target) const;

	bool getCRectSingle(CollisionRectF cRect, CollisionRectF &rect);

	void handleEvent(const sf::Event &event);

	bool isOutOfRange(int ix, int iy);

	bool isCheckPoint(int ix, int iy);

	bool isPickup(int ix, int iy);

	bool isHarmful(int ix, int iy);

	bool isClimable(int ix, int iy);

	bool isPassable(int ix, int iy);

	void update(sf::Time dt);

	void drawShadows(sf::RenderTarget& target, sf::RenderStates states);

	void drawLights(sf::RenderTarget& target);

	void drawLights(sf::RenderTarget &target, sf::RenderStates states);

	LightManager lightManager;

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	std::string file;

	int width;
	int height;

	Levels::ID loadedLevel;

	std::unique_ptr<SoftShadow> shadow;

	EnemyFactory &eFactory;

	std::vector<int> animationID;

	std::vector<TileAnimation> Animations;
	std::vector<TileData> Table;

	std::vector<std::unique_ptr<Tile>> vTiles;
};