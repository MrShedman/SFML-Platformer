#pragma once

#include <State.hpp>

#include <Tile.h>
#include <SFML\Graphics.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

class TileMap;

class TileEditor : public sf::Drawable
{
public:

	TileEditor(State::Context context, TileMap &map);

	void update();

	void handleEvent(const sf::Event &event);

private:

	void createBlock(sf::Vector2f position, TileData &data);

	void createGrid();

	void TileEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int tileID;

	bool editingMode;

	std::vector<sf::Vertex> block;
	std::vector<sf::Vertex> grid;

	TileMap &map;

	sf::Texture m_tileset;
	sf::RenderWindow &window;
};