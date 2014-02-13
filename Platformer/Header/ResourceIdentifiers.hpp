#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

class Level;

namespace Textures
{
	enum ID
	{
		TileMap,
		PlayerStanding,
		PlayerRunning,
		PlayerJumping,
		PlayerFalling,
		MenuBackground,
		GameBackground,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

namespace Levels
{
	enum ID
	{
		Level001,
		Level002,
		Level003,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<Level, Levels::ID> LevelHolder;
typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;