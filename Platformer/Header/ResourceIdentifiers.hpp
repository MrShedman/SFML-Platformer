#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		TileMap,
		PlayerStanding,
		PlayerRunning,
		PlayerJumping,
		PlayerFalling,
		PlayerClimbing,
		PlayerDying,
		MenuBackground,
		HealthBar,
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

namespace SoundEffect
{
	enum ID
	{
		PlayerJump,
		PlayerPickup,
		Button,
	};
}

namespace Music
{
	enum ID
	{
		None,
		MenuTheme,
		GameTheme001,
		GameTheme002,
		GameTheme003,
	};
}

namespace Effects
{
	enum ID
	{
		Default,
		Acid,
		Invert,
		Outline,
		PinCushion
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;