#pragma once

#include <SFML/Window/Event.hpp>

#include <Sprite.h>
#include <State.hpp>
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