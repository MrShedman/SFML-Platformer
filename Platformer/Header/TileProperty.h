#pragma once

#include <SFML\Graphics.hpp>

#define TRANSPARENT			0,  sf::Vector2f(5, 2), ' ', sf::Color(255, 255, 255, 255), true
#define COBBLESTONE			1,  sf::Vector2f(0, 0), '^', sf::Color(255, 255, 255, 255), false
#define STONE				2,  sf::Vector2f(1, 0), '*', sf::Color(255, 255, 255, 255), false
#define DIRT				3,  sf::Vector2f(2, 0), '+', sf::Color(255, 255, 255, 255), false
#define GRASS				4,  sf::Vector2f(3, 0), '~', sf::Color(255, 255, 255, 255), false
#define WOOD_PLANK			5,  sf::Vector2f(4, 0), '!', sf::Color(255, 255, 255, 255), false
#define STONE_BRICK			6,  sf::Vector2f(0, 1), '#', sf::Color(255, 255, 255, 255), false
#define CRACKED_STONE		7,  sf::Vector2f(1, 1), '?', sf::Color(255, 255, 255, 255), false
#define SAND				8,  sf::Vector2f(2, 1), '"', sf::Color(255, 255, 255, 255), false
#define GRAVEL				9,  sf::Vector2f(3, 1), '£', sf::Color(255, 255, 255, 255), false
#define WOOD				10, sf::Vector2f(4, 1), '$', sf::Color(255, 255, 255, 255), false
#define LADDER				11, sf::Vector2f(5, 1), '|', sf::Color(255, 255, 255, 255), false
#define MOSSY_STONE			12, sf::Vector2f(0, 2), '/', sf::Color(255, 255, 255, 255), false
#define BEDROCK				13, sf::Vector2f(1, 2), '%', sf::Color(255, 255, 255, 255), false
#define GLASS				14, sf::Vector2f(2, 2), '&', sf::Color(255, 255, 255, 255), false
#define TALL_GRASS			15, sf::Vector2f(3, 2), '_', sf::Color(255, 255, 255, 255), true
#define LEAVES				16, sf::Vector2f(4, 2), '@', sf::Color(255, 255, 255, 255), false
#define GOLD_ORE			17, sf::Vector2f(0, 3), '1', sf::Color(255, 255, 255, 255), false
#define IRON_ORE			18, sf::Vector2f(1, 3), '2', sf::Color(255, 255, 255, 255), false
#define DIAMOND_ORE			19, sf::Vector2f(2, 3), '3', sf::Color(255, 255, 255, 255), false
#define REDSTONE_ORE		20, sf::Vector2f(3, 3), '4', sf::Color(255, 255, 255, 255), false
#define COAL_ORE			21, sf::Vector2f(4, 3), '5', sf::Color(255, 255, 255, 255), false

class TileProperty
{
public:
	TileProperty(int ID, sf::Vector2f texCoords, char txt, sf::Color color, bool passable)
		:
		ID(ID),
		texCoords(texCoords),
		txt(txt),
		color(color),
		passable(passable)
	{}

	const int ID;
	const char txt;
	const sf::Vector2f texCoords;
	const sf::Color color;
	const bool passable;

	static sf::Vector2f texSize;
	static sf::Vector2f tileSize;
};