#pragma once

#include <ResourceIdentifiers.hpp>
#include <State.hpp>
#include <SFML/Graphics.hpp>

#include <TileAnimation.h>

#include <vector>
#include <map>

namespace Block
{
	enum ID;
}

namespace BlockAnimation
{
	enum ID;
}

struct LightData
{
	sf::Color color;
	float radius;
	float flickerFrequency;
	float flickerAmount;
};

struct TileData
{
	Block::ID type;
	char txt;
	sf::Vector2f texCoords;
	sf::Color color;
	bool passable;

	bool light;
	LightData lightData;

	BlockAnimation::ID animation;

	static sf::Vector2i texSize;
	static sf::Vector2i tileSize;
};

std::vector<TileData>	initializeTileData();

std::vector<TileAnimation> initializeTileAnimations(State::Context context);