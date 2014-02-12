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

	void pollEvent(const sf::Event &event);

private:

	void TileEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int tileID;

	bool isOn;

	sf::RectangleShape border;
	sf::Sprite block;
	sf::Texture m_tileset;

	TileMap &map;

	sf::RenderWindow *window;
};