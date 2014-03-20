#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Sprite.h>
#include <State.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <Scoreboard.h>

class PlayerSprite : public Sprite
{
public:
	PlayerSprite(State::Context context);
	virtual ~PlayerSprite();
	void handleEvent(const sf::Event &event);

	void reset();

	Scoreboard scoreboard;
	SoundPlayer &sounds;
};