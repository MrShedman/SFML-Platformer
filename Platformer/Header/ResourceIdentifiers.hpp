#pragma once

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Image;
	class Font;
	class SoundBuffer;
}

class Animation;

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
		EnemyWalking,
		EnemyFalling,
		MenuBackground,
		HealthBar,
		Fire,
		Lava,
		Portal,
		Water,
		Light,
	};
}

namespace Images
{
	enum ID
	{
		DayNightPalette,
	};
}

namespace Animations
{
	enum ID
	{
		Standing,
		Running,
		Jumping,
		Falling,
		Climbing,
		Dying,
		EnemyWalking,
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
		PlayerDeath,
		PlayerSpawn,
		Checkpoint,
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
typedef ResourceHolder<sf::Image, Images::ID>				ImageHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;